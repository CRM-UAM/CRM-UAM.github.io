#define LED 13

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

void setup() {
   Serial.begin(19200);
   //Serial.println("Hello World!! :D");
   
   delay(100);
   // Blink a little when receiving any data
   pinMode(LED, OUTPUT);
}

byte par[3]={30,50,70};
byte val[3]={0,0,0};
void loop(){
      digitalWrite(LED,LOW);
      delay(100);
      digitalWrite(LED,HIGH);
      recibirParametros(par);
     /* for(int i=0;i<3;i++){
        if(par[i]>=20){
          val[i]=(par[i]+random(-20,20));
        }else{
          val[i]=par[i];
        }
      }*/
      par[0]=map(analogRead(A0),0,1023,0,255);
      par[1]=map(analogRead(A1),0,1023,0,255);
      par[2]=map(analogRead(A2),0,1023,0,255);
      enviarTelemetria(par,3);
      
      
}


