#include "slayerUART.h"
#include <stdio.h>
#include <sys/poll.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define BIT_TEST(x,i)	((x>>i)&0x01)
#define BIT_SET(x,i)	((0x01<<i)|x)
#define BIT_CLEAR(x,i)  ((0xFF^(0x01<<i))&x)

#define FLAG_DCHA	1
#define FLAG_IZQDA	2

#define DCHO	0
#define IZQDO	1

double AT = 0.1, tiempo=0.0;
FILE *fichero;

int borde=DCHO;
int flag_centro=0;
int flag_bifurcando=0;
double error;
typedef struct
{
  double dState;      	// Last position input
  double iState;      	// Integrator state
  double iMax, iMin;
  // Maximum and minimum allowable integrator state
  double	iGain,    	// integral gain
        	pGain,    	// proportional gain
         	dGain;     	// derivative gain
} SPid;
double UpdatePID(SPid * pid, double error, double position);

unsigned char sensores=0;
unsigned char sensoresPIC=0;

int tabla[] =   { 0, 6, 4,5, 3, 0, 4, 9,1, 0, 0, 0, 2, 0,9, 9, 0, 0, 0, 0, 0 };
//int tabla[] = { 0, 7, 5-1,6-1, 3, 0, 4-1, 12-3,1, 0, 0, 0, 2, 0,12-3, 12-3, 0, 0, 0, 0, 0 };      BUENA
//int tabla[] = { 0, 9, 7,6, 5, 0, 8, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0 };
//int tabla[] = { 0, 14, 10,12, 9, 0, 8, 0, 2, 0, 0, 0,4, 0, 0, 0, 0, 0, 0, 0, 0 };
//int tabla[] = { 0, 7, 9,10, 5, 0, 6, 0,1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0 };
//int tabla[] = { 0, 9,7,8, 5, 0, 6, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0 };
int fd;
int flag_salir=0;
int estadobifur=0;
int flag_ignorar=0;	
int PID();

void *muestrear(void *arg) {
	char select[16];
	int i;
	//printf("Soy el HILO\n");
	while(1) {
		//printf("Thread: Valor anterior %s\n", select);
		recibir(fd,select,15);
		select[1]='\0';
		
		//printf("Thread: Valor leido %u\n", (unsigned char)select[0]);
		sensoresPIC=(unsigned int) select[0];
		for(i=0;i<8;i++) {
			if( BIT_TEST(sensoresPIC,i) )
				printf("X");
			else
				printf("_");
		}
		if( borde == DCHO )
			printf("\tDCHO\t%lf",error);
		else
			printf("\tIZQDO\t%lf",error);
		printf("\n");
		//printf("KK %u\n", sensoresPIC);
		}

	return NULL;

}

void handler(int sn) {
/*	fprintf(fichero,"\n");
	fclose(fichero);*/
flag_salir=1;

}


int detect2(int data, int ini, int end, int *dist) {

	int i;
	int est=0;
	int cont=1;
	//printf("asd");
	for( i=ini; i<=end; i++ ) {

		switch(est) {

			case 0:
				if (  BIT_TEST(data,i)  )
					est=1;
				break;

			case 1:
				if( !(BIT_TEST(data,i)) )
					est=2;
				break;

			case 2:
				if( BIT_TEST(data,i) )
					est=3;
				else
					cont++;
				break;
			case 3:
				break;

			}

	}

	
	if( est == 3 ) {
		//printf("distancia = %d\n",cont);
		*dist=cont; //ojo con los puteros en el pic
		return 1;
	}
	return 0;
}

int detect(int data, int ini, int end) {

	int i;
	int est=0;
	int cont=1;
	for( i=ini; i<=end; i++ ) {

		switch(est) {

			case 0:
				if (  BIT_TEST(data,i)  )
					est=1;
				break;

			case 1:
				if( !(BIT_TEST(data,i)) )
					est=2;
				break;

			case 2:
				if( BIT_TEST(data,i) )
					est=3;
				else
					cont++;
				break;
			case 3:
				break;

			}

	}

	
	if( est == 3 ) {
		return 1;
	}
	return 0;
}


int main() {

	char select[10];
	char comando[100];
	struct pollfd *ufds;
	pthread_t muestreo;

	int Kp,Kd,Ki;
	float T=0.0001;			// tiempo de muestreo
	int Tp, Td, Ti;
	int ret;
	int leido=0;
	int sensores2,aux;
	double  position;
	SPid pid;
	int i;
	int  error_anterior=0;
	int pos_servo=0x8C, integral=0;
	int flag=-1;
	int est90=0;
	int estadobifur=0;
	int dist, dist_anterior;
	int bifur;
	int kaka=0;
	int kambio=0;
	int sensores_anterior=0;
	int flag_hasta_blanco=0;
	//int flag_ignorar=0;
	signal(SIGINT,handler);
	
	
	fd=serial_open("/dev/ttyS0");
	
	pid.iMax=125; pid.iMin=1;
	pid.pGain = 1.2;
	pid.dGain = 0.0;
	pid.iGain = 0.0;
	position = 0x8C;
	pid.dState=0;

	pthread_create(&muestreo,NULL,muestrear,NULL);

	comando[0]=(unsigned char)255;
	comando[1]='\r';
	comando[2]=130;
	comando[3]='\r';
	comando[4]='\0';
	
	
	
	enviar(fd,comando,5);

	while(flag_salir!=1) {


	sensores_anterior=sensores;
	sensores=sensoresPIC;
		
	  /*if (!(BIT_TEST(sensores,3) && BIT_TEST(sensores,2) && BIT_TEST(sensores,1)) && (kambio)) {
		  borde = kambio;
		  kambio = 0;
		  flag_centro=0;
	  }*/

	  /* Modificaciones */
/*	  if( borde == DCHO &&  BIT_TEST(sensores,0) ) {
		  
		  error=-10.0;			// girar mogollón a la derecha
		  position+=UpdatePID(&pid, error, error);
		  comando[0]=(unsigned int)position;
		  comando[1]='\r';
	      comando[2]='\0';
		  enviar(fd,comando,strlen(comando));		// Enviamos la corrección calculada al PIC
		  continue;
		  
	  }
	  else {
		  
	  if( borde == IZQDO &&  BIT_TEST(sensores,7) ) {
		  
		  error=10.0;			// girar mogollón a la derecha
		  position+=UpdatePID(&pid, error, error);
		  comando[0]=(unsigned int)position;
		  comando[1]='\r';
	      comando[2]='\0';
		  enviar(fd,comando,strlen(comando));		// Enviamos la corrección calculada al PIC
		  continue;
		  }
 		}	  */
	  /* End modificaciones */
	  bifur = detect(sensores,0,7);
          switch(estadobifur) {
            case 0:
               if(bifur == 1 )
                  estadobifur=1;
               break;
            case 1:
               if(bifur == 0 ) {
				/*   if(flag_ignorar == 0 ) {
				   printf("marca\n");*/
				   //if( !detect(sensores_anterior,0,7) ) {
                   	borde=flag_bifurcando;
				   //kambio = flag_bifurcando;
                   	flag_centro=0;
					estadobifur=0;
				   //}
                   //flag_ignorar=1;
				    
			   }
               
               break;

         }
		
		/* if (!(BIT_TEST(sensores,3) && BIT_TEST(sensores,2) && BIT_TEST(sensores,1)) && (kambio)) {
		  borde = kambio;
		  kambio = 0;
		  flag_centro=0;
		
	  } */
	/* Modificaciones */
		//if (  borde == DCHO && BIT_TEST(sensores,3) && BIT_TEST(sensores,1) && BIT_TEST(sensores,2) &&  !detect(sensores_anterior,0,7) && (!(BIT_TEST(sensores_anterior,3) && BIT_TEST(sensores_anterior,1) && BIT_TEST(sensores_anterior,2)) ) ) {

if (  borde == DCHO && BIT_TEST(sensores,3) && BIT_TEST(sensores,1) && BIT_TEST(sensores,2) &&  !detect(sensores_anterior,0,7) && (!(BIT_TEST(sensores_anterior,3) && BIT_TEST(sensores_anterior,1) && BIT_TEST(sensores_anterior,2)) ) ) {		 
			printf("movida\n");
			error=-40.0;
		
			position+=UpdatePID(&pid, error, error);
			if( position >= 250.0 )
				position =250.0;
			else 
				if( position <= 5.0 )
					position =5.0;
				//position-=80.0;
			comando[0]=(unsigned int)position;
			comando[1]='\r';
			comando[2]='\0';
			enviar(fd,comando,strlen(comando));		// Enviamos la corrección calculada al PIC
			//usleep(200000);			
			continue;
			

		}
	/* end mod */
		
if (  borde == IZQDO && BIT_TEST(sensores,6) && BIT_TEST(sensores,5) && BIT_TEST(sensores,4) &&  !detect(sensores_anterior,0,7) && (!(BIT_TEST(sensores_anterior,6) && BIT_TEST(sensores_anterior,5) && BIT_TEST(sensores_anterior,4)) ) ) {		 
			printf("movida\n");
			error=40.0;
		
			position+=UpdatePID(&pid, error, error);
			if( position >= 250.0 )
				position =250.0;
			else 
				if( position <= 5.0 )
					position = 5.0;
				//position-=80.0;
			comando[0]=(unsigned int)position;
			comando[1]='\r';
			comando[2]='\0';
			enviar(fd,comando,strlen(comando));		// Enviamos la corrección calculada al PIC
			//usleep(200000);			
			continue;
			

		}

		

		/*if( flag_hasta_blanco==1 ) {
			if( !BIT_TEST(sensores,3) && !BIT_TEST(sensores,4) && !BIT_TEST(sensores,2) && !BIT_TEST(sensores,5) )
				flag_hasta_blanco = 0;
			else
				continue;
			
		}*/
			
	      switch(borde) {


			  
          case DCHO:


          if( (BIT_TEST(sensores,3) == 1) && (BIT_TEST(sensores,2) == 0 ) )  {      /* 10 */
             flag_centro=0;
			  error=0.0;
             if( bifur ) {
            		if( detect(sensores,3,7) )
                        flag_bifurcando =IZQDO;
            		else
            			flag_bifurcando = DCHO;
                      	}
              continue;

          }

          if( (BIT_TEST(sensores,3) == 0) && (BIT_TEST(sensores,2) == 1 ) )  {      /* 01 */
             error=(float)-1.0*1;
             flag_centro=1;
             }
         if( (BIT_TEST(sensores,3) == 0) && (BIT_TEST(sensores,2) == 0) )  {        /* 00 */
            if(flag_centro) {
               error=(float)-1.0*1;
                if(bifur) {
                     if( detect(sensores,0,2) )
                        flag_bifurcando=DCHO;
                     else
                         flag_bifurcando=IZQDO;
                       }
                  }
            else  {
               error=(float)1;
               if(bifur) {
                     if( detect(sensores,3,7) )
                        flag_bifurcando=IZQDO;
            
                     else
                         flag_bifurcando=DCHO;
            
                  }
               }
			                /* ultima hora */
        	if(!bifur) {
		   	if( sensores > 0x0F) {
	     		aux=0;
		    	sensores2 = sensores >> 4;
   				for(i=0;i<4;i++) {
	     			if ( BIT_TEST(sensores2,i) )
		    			aux=BIT_SET(aux,3-i);
              	}
   				error = (float)tabla[aux];
   		    }

			else {
            if( sensores < 0x0F )
				error = (float)-1.0*tabla[sensores];
      		}
			}
            /* fin ultima hora */ 


         }
         if( (BIT_TEST(sensores,3) == 1) && (BIT_TEST(sensores,2) == 1) )   {       /* 11 */
            error=(float)-1.0*1;
            flag_centro =1;
            if( bifur ) {
               		if( detect(sensores,3,7) )
               			flag_bifurcando = IZQDO;
               		else
               			flag_bifurcando = DCHO;
                     	}
         }
         break;
         case IZQDO:
		// error negativo = girar dcha
         if( (BIT_TEST(sensores,5) == 0) && (BIT_TEST(sensores,4) == 1 ) )  {      /* 01 */
             flag_centro=0;
             if( bifur ) {
            		if( detect(sensores,0,4) )
                        flag_bifurcando = DCHO;
            		else
              			flag_bifurcando = IZQDO;
            	}
             continue;

          }

          if( (BIT_TEST(sensores,5) == 1) && (BIT_TEST(sensores,4) == 0 ) )  {      /* 10 */
             error=(float)1;
             flag_centro=1;
               }
         if( (BIT_TEST(sensores,5) == 0) && (BIT_TEST(sensores,4) == 0) )  {        /* 00 */
            if(flag_centro) {
               error=(float)1;
               if(bifur) {
                     if( detect(sensores,5,7) )
                        flag_bifurcando=IZQDO;
                     else
                         flag_bifurcando=DCHO;
                      }
            }
            else {
               error=(float)-1.0*1;
               if(bifur) {
                     if( detect(sensores,0,3) )
                        flag_bifurcando=DCHO;
        
                     else
                         flag_bifurcando=IZQDO;
        
                  }
            }
			
			             /* ultima hora */
        	if(!bifur) {
		   	if( sensores > 0x0F) {
	     		aux=0;
		    	sensores2 = sensores >> 4;
   				for(i=0;i<4;i++) {
	     			if ( BIT_TEST(sensores2,i) )
		    			aux=BIT_SET(aux,3-i);
              	}
   				error = (float)tabla[aux];
   		    }

			else {
            	if( sensores < 0x0F )
					error = (float)-1.0*tabla[sensores];
      		}
		}
            /* fin ultima hora */ 


         }
         if( (BIT_TEST(sensores,5) == 1) && (BIT_TEST(sensores,4) == 1) )   {       /* 11 */
            error=(float)1;
            flag_centro =1;
            if( bifur ) {
               		if( detect(sensores,0,4) )
               			flag_bifurcando = DCHO;
              		else
               			flag_bifurcando = IZQDO;
                   	}

         }

         } // fin switch(borde)

	/*  bifur = detect(sensores,0,7,&dist);
         switch(estadobifur) {
            case 0:
               if(bifur == 1 ) {
                  estadobifur=1;
				  dist_anterior=dist;
				   kaka=0;
			   }
               break;
            case 1:
			   if( !( ((dist_anterior - dist) >= -1) && ((dist_anterior - dist) <= 1) )  ) {
				   kaka=1;
			   }
			   dist_anterior=dist;
               if(bifur == 0 ) {
				   
				    if( kaka == 0 ) 
						printf("MARCA DETECTADA\n");
      		   
                   estadobifur=0;
               }
               break;

         }
	
	if(est90==1) {
		
		if(sensores != 128 && sensores != 1 && sensores != 0)
			est90=0;
		
	}
	
	if(est90 == 0 ) {
	if(sensores == 24 || sensores == 0) {
		tiempo+=AT;
		continue;
		
	}
	if( sensores > 0x0F) {
		

			aux=0;
			sensores2 = sensores >> 4;

			for(i=0;i<4;i++) {
				if ( BIT_TEST(sensores2,i) )
					aux=BIT_SET(aux,3-i);
			}
			error = tabla[aux];
			if( error == 12 ) {
				//est90=1;
				//printf("90 grados\n");
			}
			flag=FLAG_IZQDA;

		}

			else {
				error = -tabla[sensores];
				if( error == 12 ) {
				printf("90 grados\n");
				}
			
				flag=FLAG_DCHA;

			}
		}*/
//	tiempo+=(double)AT;
	
	if( sensores == 0 )
		error=pid.dState;
	
	position+=UpdatePID(&pid, error, error);
	if( position >= 250.0 )
		position =250.0;
	else 
		if( position <= 5.0 )
			position =5.0;

	comando[0]=(unsigned int)position;
	comando[1]='\r';
	comando[2]='\0';
	/*sprintf(comando,"1\r%d\r",(int)position);*/
	enviar(fd,comando,strlen(comando));		// Enviamos la corrección calculada al PIC

	usleep(1);

	} // fin while
	//sprintf(comando,"\r0\r"); // veloc=120
	comando[0]=255;
	comando[1]='\r';
	comando[2]=0;
	comando[3]='\r';
	comando[4]='\0';
	//enviar(fd,comando,5);

	return 0;
}

double UpdatePID(SPid * pid, double error, double position)
{
  double pTerm,dTerm, iTerm;
  pTerm = pid->pGain * error;
  pid->iState += error;
  if (pid->iState > pid->iMax) pid->iState = pid->iMax;
  else if (pid->iState <  pid->iMin) pid->iState = pid->iMin;
  iTerm = pid->iGain * pid->iState;
  dTerm = pid->dGain * (position - pid->dState);
  pid->dState = position;
  return pTerm + iTerm - dTerm;
}
