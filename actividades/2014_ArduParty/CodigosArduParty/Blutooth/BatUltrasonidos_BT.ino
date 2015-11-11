#include "Servo.h"

#define CM 1      //Centimeter
#define INC 0     //Inch
#define TP 8      //Trig_pin
#define EP 9      //Echo_pin
#define LED 13

Servo s_der;
Servo s_izq;

void motor_der(int pot){
 int p=-pot;
  if((p+100)>180){
   s_der.write(180);
  }else{
   s_der.write(p+100);
  } 
}

void motor_izq(int pot){
 int p=pot;
  if((p+92)>180){
   s_izq.write(180);
  }else{
   s_izq.write(p+92);
  } 
}


 
long Distance(long time, int flag)
{
  /*
 
  */
  long distacne;
  if(flag)
    distacne = time /29 / 2  ;     // Distance_CM  = ((Duration of high level)*(Sonic :340m/s))/2
                                   //              = ((Duration of high level)*(Sonic :0.034 cm/us))/2
                                   //              = ((Duration of high level)/(Sonic :29.4 cm/us))/2
  else
    distacne = time / 74 / 2;      // INC
  return distacne;
}
 
long TP_init()
{                     
  digitalWrite(TP, LOW);                    
  delayMicroseconds(2);
  digitalWrite(TP, HIGH);                 // pull the Trig pin to high level for more than 10us impulse 
  delayMicroseconds(10);
  digitalWrite(TP, LOW);
  long microseconds = pulseIn(EP,HIGH);   // waits for the pin to go HIGH, and returns the length of the pulse in microseconds
  return microseconds;                    // return microseconds
}

boolean recibirParametros(byte *par){
  String msg="";
  if(Serial.available() == 0)return false;
  delay(5);
  while(Serial.available()>0){
    char c=Serial.read();
    msg+=c;
    if(c=='\n')break;
  }
  Serial.flush();
  for(int i=0;i<3;i++){
    par[i]=msg.substring(0,msg.indexOf(',')).toInt();
    msg=msg.substring(msg.indexOf(',')+1);
  }
  return true;
}

void enviarTelemetria(byte *val, int num){
  char cad[16]={0};
  String msg=String("-T "+String(num)+" "+String(val[0])+" "+String(val[1])+" "+String(val[2]));
  msg.toCharArray(cad,16);
  Serial.println(cad);
   
}
 byte par[3];

void setup(){
  pinMode(TP,OUTPUT);       // set TP output for trigger  
  pinMode(EP,INPUT);        // set EP input for echo
  pinMode(LED,OUTPUT);
  Serial.begin(19200);      // init serial 9600
  s_der.attach(11);
  s_izq.attach(10);
  //Serial.println("-------------------BAT_Demo_Start---------------------------------");
}


void loop(){  
  long microseconds = TP_init();
  par[0]=map(microseconds,0,15000,0,255);
  //Serial.print("ret=");      //
  //Serial.println(microseconds);
  long distance_cm = Distance(microseconds, CM);
  par[0]=distance_cm;
  enviarTelemetria(par,2);
  //Serial.print("Distacne_CM = ");
  //Serial.println(distance_cm);
  delay(500);
  
  if(recibirParametros(par)==true){
    motor_der(map(par[0],0,100,-90,90));
    motor_izq(map(par[1],0,100,-90,90));
  }
}
