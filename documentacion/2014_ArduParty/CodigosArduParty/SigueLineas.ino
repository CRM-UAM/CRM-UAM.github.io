#include "Servo.h"

#define LED 13
#define IR_1 2
#define IR_2 3
#define IR_3 4
#define IR_4 5

#define Kp 7
#define VEL_BASE 30

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

boolean ir1,ir2,ir3,ir4;
int linea=0;

void setup(){
  pinMode(LED,OUTPUT);
  pinMode(IR_1,INPUT);
  pinMode(IR_2,INPUT);
  pinMode(IR_3,INPUT);
  pinMode(IR_4,INPUT);
  
  s_der.attach(11);
  s_izq.attach(10);
  
}

void loop(){
  ir1=digitalRead(IR_1);
  ir2=digitalRead(IR_2);
  ir3=digitalRead(IR_3);
  ir4=digitalRead(IR_4);
  
  if(ir1==HIGH && ir2==LOW && ir3==LOW && ir4==HIGH){
    linea=0;
  }else if(ir1==HIGH && ir2==LOW && ir3==HIGH && ir4==HIGH){
    linea=0.5;
  }else if(ir1==LOW && ir2==LOW && ir3==HIGH && ir4==HIGH){
    linea=1.5;
  }else if(ir1==LOW && ir2==HIGH && ir3==HIGH && ir4==HIGH){
    linea=2.5;
  }else if(ir1==HIGH && ir2==HIGH && ir3==LOW && ir4==HIGH){
    linea=-0.5;
  }else if(ir1==HIGH && ir2==HIGH && ir3==LOW && ir4==LOW){
    linea=-1.5;
  }else if(ir1==HIGH && ir2==HIGH && ir3==HIGH && ir4==LOW){
    linea=-2.5;
  }else if(ir1==HIGH && ir2==HIGH && ir3==HIGH && ir4==HIGH){
    if(linea<0){
      linea=-4;
    }else{
      linea=4;
    }
  }else{linea=-100;}
  
  if(linea<-90){
    motor_der(0);
    motor_izq(0);
  }else{
    motor_der(VEL_BASE +Kp*linea);
    motor_izq(VEL_BASE -Kp*linea);
  }
  //motor_der(0);
  //motor_izq(0);
}
