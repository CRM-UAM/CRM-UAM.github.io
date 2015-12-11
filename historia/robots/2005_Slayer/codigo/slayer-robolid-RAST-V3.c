#include <16F877A.h>
//#include <18F8720.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>


#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=4000000)
#use fast_io(C)
#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7,BRGH1OK)


/*#define  KP 1
#define  KD  1
#define  KI  1*/
#define SERVO_INIT   135
#define PWM_INIT  450
#define IZQDA  1
#define DCHA   2


#define SAT_DCHA      3      // bit 2 del puerto a
#define SAT_IZQDA     5

//int tabla[] = { 0, 7, 5,6, 3, 0, 4, 12,1, 0, 0, 0, 2, 0, 12, 12, 0, 0, 0, 0, 0 };

const int tabla[] =   { 0, 8, 5, 6, 3, 0, 4, 0,1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0 };


unsigned int sat;


//char select[10];
//long valor;
//int KP;

/*#int_rda

rcv_handler() {
   printf("entro\r");
   gets(select);
   KP=atoi(select);
}*/

#define FLAG_DCHA	1
#define FLAG_IZQDA	2

#define DCHO   1
#define IZQDO  2

#define EXTREMO_IZQDA   243   // Para optimizar consumo
#define EXTREMO_DCHA    14

//float AT=0.0;

//FILE *fichero;


typedef struct
{
  float dState;      	// Last position input
  float iState;      	// Integrator state
  float iMax, iMin;
  // Maximum and minimum allowable integrator state
  float	iGain,    	// integral gain
        	pGain,    	// proportional gain
        	dGain;     	// derivative gain
} SPid;

float UpdatePID(SPid * pid, float error, float position);


int borde=DCHO   ;

int flag_inicio = 1;

unsigned int flag_bifurcando=0;
unsigned long delaymov=0;

float position;
unsigned long pwm=PWM_INIT;


unsigned int flag_movida = 0;
unsigned int flag_movida_aux = 0;


/*void function_speed() {
           if( ( (unsigned int)position >(SERVO_INIT-50) && (unsigned int)position < (SERVO_INIT-20) )  || ( (unsigned int)position > (SERVO_INIT+20) && (unsigned int)position <(SERVO_INIT+50) )   )

               set_pwm1_duty(pwm-40);

           else {

              if( ( (unsigned int)position > (SERVO_INIT-70) && (unsigned int)position < (SERVO_INIT-50) )  || ( (unsigned int)position > (SERVO_INIT+50) && (unsigned int)position <(SERVO_INIT+70) )   )
                    set_pwm1_duty(pwm-80);

              else {

                  if( ( (unsigned int)position > (SERVO_INIT-90) && (unsigned int)position < (SERVO_INIT-70) )  || ( (unsigned int)position > (SERVO_INIT+70) && (unsigned int)position <(SERVO_INIT+90) )   )
                    set_pwm1_duty(pwm-120);

                   else {

                       if( ( (unsigned int)position > 0 && (unsigned int)position < (SERVO_INIT-90) )  || ( (unsigned int)position > (SERVO_INIT+90) && (unsigned int)position < 255 )   )
                          set_pwm1_duty(pwm-180);
                        else {
                                       set_pwm1_duty(pwm);
                        }

                   }


              }


           }


}*/


int test90(unsigned int sensores);
/* devuelve <0 si izqda, >0 si dcha, 0 si no hay 3 sensores en negro */
/*int cont=0;
#INT_TIMER1
void handler() {
   cont++;
   if( cont == 7 ) {
                  borde=flag_bifurcando;
                  cont=0;
                  disable_interrupts(INT_TIMER1);

   }

}*/

/* devuelve 1 si hay dos fragmentos de negro y 0 si no */
int detect(int data, int ini, int end) {

	int i;
	int est=0;

// bits mas pequeños -> mas a la dcha

	for( i=ini; i<=end; i++ ) {

      if( i == 0 ) {
         if( bit_test(sat,SAT_DCHA) )
            est=1;
      }


		switch(est) {

			case 0:
				if (  bit_test(data,i) == 1 )
					est=1;
				break;

			case 1:
				if( bit_test(data,i) == 0 )
					est=2;
				break;

			case 2:
				if( bit_test(data,i) == 1)
					est=3;
				break;
			case 3:
				break;

			} //switch



         if( i==7 ) {
            if( bit_test(sat,SAT_IZQDA) && est == 2 )
               est=3;

         }






	} // for

	if( est == 3 )
		return 1;
	return 0;
}



void main() {



   unsigned  int sensores, aux,  sensores_anterior;
//   int kk, cero=0;

   float error;
   int flag;
   int estado=0;
   int flag2;
   char select[6];
   unsigned int cmd;
   int flag_centro=0;
   int estadobifur=0;
   int flag_ignorar=0;
   unsigned int sensores2;

   int i;
   int  bifur;
   SPid pid;

   unsigned int flag90=0;

   int extremo=90;

   set_tris_d(0x00);
   set_tris_b(0xFF);
   set_tris_c(0x80);
//   set_tris_a(0x02);

    set_tris_a(0b11111110);


   output_c(0xFF);

   pid.iMax=125; pid.iMin=1;
	pid.pGain = 0.13;   // estaba a 0.11, y kd a 0.02
	pid.dGain = 0.02;
	pid.iGain = 0.0;
	position = 135;     //estaba a 140
	pid.dState=0;

 //  KPaux=pid.pGain;
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);   // setup interrupts
//   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);



   setup_ccp1(CCP_PWM);       // CCP1 como PWM
   setup_timer_2(T2_DIV_BY_1, 255, 1);    //  TIMER2 con 1:1 y PR2 a FF lo que da una Fpwm=19531,25 Hz con Fosc=20Mhz


   set_pwm1_duty(pwm);

   output_d(SERVO_INIT);


   output_high(PIN_A0);
//   anterior=0;

   printf("=============== RESET ===================\r\n");
   while(1) {

      if( !input(PIN_A1) ) {
         if(estado==1) {
            estado=0;
            set_pwm1_duty(pwm);
         }
          else
            estado=1;
         printf("Cambio de estado.Kp:%f Kd:%f Ki:%fBORDE:%d\r\n",pid.pGain,pid.dGain,pid.iGain,borde);
         while(!input(PIN_A1));
         }

   else {

         if( flag_inicio == 1 )  {
            flag_inicio=0;
            estado=1;
            output_d(SERVO_INIT);
         }

       }


      switch(estado) {

         case 1:
            set_pwm1_duty(0);
            if( kbhit() ) {
               gets(select);
               if( flag2 == 0 ) {
                  flag2=1;
                  cmd=atoi(select);
                  printf("Comando: %d\r\n",cmd);
                  }
              else {
                  switch(cmd) {

                     case 1:
                          pid.pGain=strtod(select,NULL);
                          printf("pgain: %f\r\n",pid.pGain);
                        //  KPaux=pid.pGain;
                          break;
                     case 2:
                          pid.dGain=strtod(select,NULL);
                          printf("dgain: %f\r\n",pid.dGain);
                          break;
                     case 3:
                          pid.iGain=strtod(select,NULL);
                          printf("igain: %f\r\n",pid.iGain);
                          break;
                     case 4:
                          pwm = strtol(select,NULL,10);
                          printf("Vel: %ld\r\n",pwm);
                          break;
                     case 5:
                         delaymov=strtol(select,NULL,10);
                         printf("delay: %ld\r\n",delaymov);
                         break;
                     case 6:
                         extremo=strtod(select,NULL);
                         printf("Extr: %d\r\n",extremo);
                         break;



                       /* pwm=atoi(select);
                        set_pwm1_duty(pwm);*/
                        }
                  flag2=0;

                   }

            }
            break;

         case 0:

//         pwm+=(int)(error*10.0);
//         if( error > 0.0 )
//            set_pwm1_duty(pwm-(int)(error*15.0));
  //       else

//         function_speed();

         if(sensores!=0)
            sensores_anterior=sensores;

         sensores=input_b();
         //sat = input_a();
         
         if( input(PIN_A3) ) 
            bit_set(sat,3);         
         else
            bit_clear(sat,3);
         
         
         if( input(PIN_A5) ) 
            bit_set(sat,5);         
         else
            bit_clear(sat,5);
         
         
      //   printf("Leido:   %d:%d  %d:%d\r\n",bit_test(sat,SAT_DCHA),bit_test(sat,3),bit_test(sat,SAT_IZQDA),bit_test(sat,5));

/*  DEBUGGING       if(sensores != sensores_anterior ) {

         printf("D: ");
         for(i=0;i<8;i++) {
            if( bit_test(sensores,i) )
               printf("X");
            else
               printf("_");
         }
         if( borde == DCHO )
             printf("  D");
         else
             printf("  I");
         printf("\r\n");
         }*/


/*         if( borde == DCHO ) {

               if( test90( (sensores&0x0F) ) == 2 ) {

                     error=(float)-10.0;
                     	position+=UpdatePID(&pid, error, error);
                     if( position > 255.0)
                        position = 255.0;
                     if ( position < 0.0 )
                        position = 0.0;
                     output_d((unsigned int)position);
                                          continue;

               }

          }
        if( borde == IZQDO) {

                if( test90((sensores&0xF0)) == 1 ) {
                     error=(float)10.0;
                     	position+=UpdatePID(&pid, error, error);
                     if( position > 255.0)
                        position = 255.0;
                     if ( position < 0.0 )
                        position = 0.0;
                     output_d((unsigned int)position);
                     continue;
               }




        }*/

/*         if( sensores == 24 )       /* 11
            continue;*/

            // meter flag ignorandobif
        /*  if( test90(sensores)==1 && borde == DCHO ) {

                  if( pid.pGain == KPaux)
                     pid.pGain = pid.pGain+pid.pGain+pid.pGain+pid.pGain;

          }*/

          bifur = detect(sensores,0,7);
          switch(estadobifur) {
            case 0:
               if(bifur == 1 )
                  estadobifur=1;
               break;
            case 1:
               if(bifur == 0 && !( bit_test(sensores,3) && bit_test(sensores,4)) ) {
                  /* Cuando dejemos de ver bifurcacion cambiamos de borde SALVO que los sensores centrales vean blanco */

                  flag2=0;
                  for(i=0;i<7;i++) {
                     if( bit_test(sensores,i) == 1 )
                        flag2++;
                  }

                  if(flag2 <= 2 ) {

                   borde=flag_bifurcando;

                   if( borde == DCHO )
                     output_high(PIN_A0);
                   else
                     output_low(PIN_A0);

                   flag_centro=1;
                   estadobifur=0;
                   }
               }
               break;

         }
/*          if( bifur == 0 )
            enable_interrupts(INT_TIMER1);
          else
            disable_interrupts(INT_TIMER1);*/
//            borde=flag_bifurcando;

/*          if( flag_marca == 1 && bifur == 1 )
            flag_marca=0;*/




/*XXXX    if( flag_movida != 0 ) {


      
    
    if( flag_movida == DCHO ) {
         position=0.0+(double)extremo;
         output_d((unsigned int)position);
         delay_ms(delaymov);
         flag_movida = 0;     
         flag_movida_aux = 0;  
			continue;
      }
      
      if( flag_movida == IZQDO ) {
         position=255.0-(double)extremo;
         output_d((unsigned int)position);
         delay_ms(delaymov);
         flag_movida = 0;     
         flag_movida_aux = 0;     
   		continue;
      }
         
    } */




//if (  borde == DCHO && bit_test(sensores,3) && bit_test(sensores,2) && bit_test(sensores,1) && !detect(sensores_anterior,0,7) && (!(bit_test(sensores_anterior,3) && bit_test(sensores_anterior,1) && bit_test(sensores_anterior,2)) ) ) {



/*XXXX if(  borde == DCHO && (test90(sensores)==2) &&  !detect(sensores_anterior,0,7)   && !(test90(sensores_anterior)==2) ) {

   flag_movida_aux = DCHO;
   

		}
      
else {

      if( flag_movida_aux == DCHO )
         flag_movida = DCHO;

}*/




    

//if (  borde == IZQDO && bit_test(sensores,6) && bit_test(sensores,5) && bit_test(sensores,4) &&  !detect(sensores_anterior,0,7) && (!(bit_test(sensores_anterior,6) && bit_test(sensores_anterior,5) && bit_test(sensores_anterior,4)) ) ) {


/*XXXX if(  borde == IZQDO && (test90(sensores)==1) &&  !detect(sensores_anterior,0,7)   && !(test90(sensores_anterior)==1) ) {

   flag_movida_aux = IZQDO;
//         printf("movida a la izqda\n");



		}

else {

      if( flag_movida_aux == IZQDO )
         flag_movida = IZQDO;

}*/


         switch(borde) {


          case DCHO:

          if( (bit_test(sensores,3) == 1) && (bit_test(sensores,2) == 0 ) )  {      /* 10 */
             flag_centro=0;

             if( bifur ) {
            		if( detect(sensores,3,7) )
            			  // borde = IZQDO;
                     flag_bifurcando =IZQDO;
            		else
            			flag_bifurcando = DCHO;
                     //borde = DCHO;
            	}
          //    pid.pGain=KPaux;
              continue;


          }

          if( (bit_test(sensores,3) == 0) && (bit_test(sensores,2) == 1 ) )  {      /* 01 */
             error=(float)-1.0*1;
             flag_centro=1;



          }
         if( (bit_test(sensores,3) == 0) && (bit_test(sensores,2) == 0) )  {        /* 00 */
            if(flag_centro) {
//               error=(float)-1.0*1;
                if(bifur) {
                     if( detect(sensores,0,2) )
                        flag_bifurcando=DCHO;
                        //borde=DCHO;
                     else
                         flag_bifurcando=IZQDO;
                         //borde=IZQDO;
                  }
                  }
            else  {
  //             error=(float)1;
               if(bifur) {
                     if( detect(sensores,3,7) )
                        flag_bifurcando=IZQDO;
                      // borde = IZQDO;
                     else
                         flag_bifurcando=DCHO;
                       // borde = DCHO;
                  }
               }


/*X               if( sensores == 0 && ( bit_test(sat,SAT_DCHA) || bit_test(sat,SAT_IZQDA) ) ) {      // La linea está en los últimos sensores

                     if( bit_test(sat,SAT_DCHA) )
                           error = -10.0;

                     else
                           error = 10.0;


               }

               else {*/

                /* Modificacion 22/05/05 para saber donde esta la linea cuando ve blanco*/
               if(sensores == 0 ) {
                  if (sensores_anterior > 0x0F )
                     sensores = 0x80;
                  else
                     sensores = 0x01;
                  }


            if( !detect(sensores,0,7)  ) {
               /* ultima hora */
            	if( sensores > 0x0F) {
	     		       aux=0;
      		    	 sensores2 = sensores >> 4;
           			for(i=0;i<4;i++) {
	     			      if ( bit_test(sensores2,i) )
      		    			aux=bit_set(aux,3-i);
                   }
                  if( aux < 22 )
      			      error = (float)tabla[aux];
   		       }

        		   else {
                     if( sensores < 0x0F )
			         	error = (float)-1.0*tabla[sensores];
            		}

               /* fin ultima hora */
               }
//X               } // fin else
          }



         if( (bit_test(sensores,3) == 1) && (bit_test(sensores,2) == 1) )   {       /* 11 */
         
            if( test90(sensores) == 2 )
               error=(float)-15.0*1.0;
            else
               error=(float)-1.0*1.0;
          /*  if(flag_centro)
                flag_centro=0;
            else*/
               flag_centro =1;

               if( bifur ) {
               		if( detect(sensores,3,7) )
               			flag_bifurcando = IZQDO;
                        //borde=IZQDO;
               		else
               			flag_bifurcando = DCHO;
                        //borde=DCHO;
            	}
         }
         break;
         case IZQDO:
// error negativo = girar dcha
         if( (bit_test(sensores,5) == 0) && (bit_test(sensores,4) == 1 ) )  {      /* 01 */
             flag_centro=0;

             if( bifur ) {
            		if( detect(sensores,0,4) )
            			  //borde = DCHO;
                     flag_bifurcando = DCHO;
            		else
                     //borde=IZQDO;
            			flag_bifurcando = IZQDO;
            	}
//             pid.pGain=KPaux;
             continue;

          }

          if( (bit_test(sensores,5) == 1) && (bit_test(sensores,4) == 0 ) )  {      /* 10 */
             error=(float)1;
             flag_centro=1;



          }
         if( (bit_test(sensores,5) == 0) && (bit_test(sensores,4) == 0) )  {        /* 00 */
            if(flag_centro) {
               error=(float)1;
               if(bifur) {
                     if( detect(sensores,5,7) )
                        flag_bifurcando=IZQDO;
                        //                     borde=IZQDO;
                     else
                         flag_bifurcando=DCHO;
                        //                     borde=DCHO;
                  }
            }
            else {

               error=(float)-1.0*1;
               if(bifur) {
                     if( detect(sensores,0,3) )
                        flag_bifurcando=DCHO;
                        //borde= DCHO;
                     else
                         flag_bifurcando=IZQDO;
                         //                     borde=IZQDO;
                  }
            }


/*X              if( sensores == 0 && ( bit_test(sat,SAT_DCHA) || bit_test(sat,SAT_IZQDA) ) ) {      // La linea está en los últimos sensores

                     if( bit_test(sat,SAT_DCHA) )
                           error = -10.0;

                     else
                           error = 10.0;


               }

               else { */


               /* Modificacion 22/05/05 para saber donde esta la linea cuando ve blanco*/
               if(sensores == 0 ) {
                  if (sensores_anterior > 0x0F )
                     sensores = 0x80;
                  else
                     sensores = 0x01;
               }



        if( !detect(sensores,0,7)  ) {


   	if( sensores > 0x0F) {
	     		aux=0;
		    	sensores2 = sensores >> 4;
   			for(i=0;i<4;i++) {
	     			if ( bit_test(sensores2,i) )
		    			aux=bit_set(aux,3-i);
              }
           if( aux < 22 )
   			error = (float)tabla[aux];
   		    }

			else {
            if( sensores < 0x0F ) //{
   				error = (float)-1.0*tabla[sensores];

//            }

      		}

         }

            /* fin ultima hora */

//X               } // fin else

         }
         if( (bit_test(sensores,5) == 1) && (bit_test(sensores,4) == 1) )   {       /* 11 */


           if( test90(sensores) == 1 )
               error=(float)19.0*1.0;
            else
               error=(float)1.0;
          /*  if(flag_centro)
                flag_centro=0;
            else*/
               flag_centro =1;

               if( bifur ) {
               		if( detect(sensores,0,4) )
               			flag_bifurcando = DCHO;
                        //                     borde=DCHO;
               		else
               			flag_bifurcando = IZQDO;
                //                       borde=IZQDO;
            	}

         }

         }



	position+=UpdatePID(&pid, error, error);
   if( position > EXTREMO_IZQDA)
      position = EXTREMO_IZQDA;
   if ( position < EXTREMO_DCHA )
      position = EXTREMO_DCHA;
   output_d((unsigned int)position);

//   printf("%lf %lf\r\n",error,position);
//   printf("%u %u\r\n",sensores,(int)position);
//   printf("errorf: %f error: %f sens: %u pos: %u\r\n",error,error,(unsigned int)sensores,(unsigned int)position);
//	sprintf(comando,"1\r%d\r",(int)position);
//	enviar(fd,comando,strlen(comando));		// Enviamos la corrección calculada al PIC

//  delay_ms(4);
      }//switch
   }

}

float UpdatePID(SPid * pid, float error, float position)
{
  float pTerm,dTerm, iTerm;
//  error=-1.0;
  pTerm = pid->pGain * error;
 //   printf("pid->pGain: %lf error: %f pTerm: %lf\r\n",pid->pGain,error,pTerm);

/*  pid->iState += error;
  if (pid->iState > pid->iMax) pid->iState = pid->iMax;
  else if (pid->iState <  pid->iMin) pid->iState = pid->iMin;
  iTerm = pid->iGain * pid->iState;*/

//  dTerm = pid->dGain * (position - pid->dState);
  if(  ((int)position > 0 && (int)pid->dState < 0) || ((int)position < 0 && (int)pid->dState > 0 ) )
      dTerm = 0.0;

   else
     dTerm = pid->dGain * (position - pid->dState);

  pid->dState = position;

  return pTerm + iTerm + dTerm;
}

int test90(unsigned int sensores)  {

   unsigned int aux;

//unsigned long aux=0;


   aux=sensores&0x0F;
   aux= aux << 1;
   if( bit_test(sat,SAT_DCHA) )
      bit_set(aux,0);

   if(aux==7 || aux ==14 || aux == 28 || aux == 15 || aux== 30 || aux == 31)
      return 2;

  aux=sensores&0xF0;
  aux=aux>>4;
  if( bit_test(sat,SAT_IZQDA) )
      bit_set(aux,4);




  if(aux==7  || aux == 14 || aux == 28 || aux == 15 || aux== 30 || aux == 31)
      return 1;

  return 0;
/*   int i,cont=0,  cont2= 0,est=0;

   for(i=0;i<8;i++) {
      if(bit_test(sensores,i) ) {
         if( i>3)
            cont++;
         else
            cont2++;
         }
      }


    if( (cont+cont2)>2 ) {
     //    return (cont-cont2);
     if( cont > cont2 )
         return 1;
    else
         return 2;
    }
   else
      return 0;*/
}
