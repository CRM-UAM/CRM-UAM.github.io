float media;

void setup ()
{
  /*Las fotoresistencias disminuyen la resistencia conforme aumenta
  la iluminacion.*/
 /*Control de motores*/
 pinMode (9, OUTPUT); /*Right-Backwards.*/
 pinMode (10, OUTPUT); /*Right-Forward.*/
 pinMode (5, OUTPUT);    /*Left-Forward.*/
 pinMode (6, OUTPUT); /*Left-Backwards.*/
 pinMode (13, OUTPUT);
 pinMode (7, INPUT); //Bumper izquierdo
 pinMode (8, INPUT); //Bumper derecho
 
 int s3, s4;
 float m1, m2, m3, m4;
 
 digitalWrite(13, LOW);
 
 s3 = analogRead(A3);
 s4 = analogRead(A4);
 
 m1 = (s3+s4)/2.0;
 delay(2000);
 
 s3 = analogRead(A3);
 s4 = analogRead(A4);
 
 m2 = (s3+s4)/2.0;
 delay(2000);
 
 s3 = analogRead(A3);
 s4 = analogRead(A4);
 
 m3 = (s3+s4)/2.0;
 delay(2000);
 
 s3 = analogRead(A3);
 s4 = analogRead(A4);
 
 m4 = (s3+s4)/2.0;
 
 media = (m1+m2+m3+m4)/4.0;
 media /= 1023.0;
 media *= 200.0;
}

void loop ()
{ 
  
  /*Los sensores tienen el mismo número que el indicado en el robot.*/
  //HOYGAN, a mayor luz, menor resistencia ofrecida por las LDR, y mayor tensión obtenida. GRASIAS DE ANTEBRASO
  int sensor1, sensor2, sensor3, sensor4, bumperiz, bumperder;
  float velocidad, medida;
  
  digitalWrite(13, HIGH);
  
  sensor1 = analogRead (A1);
  sensor2 = analogRead (A2);
  sensor3 = analogRead (A3);
  sensor4 = analogRead (A4);
  
  /*La entrada 7 corresponde al bumper izquierdo; la 8, al derecho. Porque a Lucas le sale del coño.*/
  bumperiz = digitalRead (7);
  bumperder = digitalRead (8);
 
  medida = (sensor3+sensor4)/2;
  medida /= 1023.0;
  medida *= 200.0;

  velocidad = media - medida;
  
  if (bumperiz == 1)
  {
    motion (-1, -1, 100, 200);
    delay (500);
    motion (1, 1, 200, 200);
    delay (1500);
  }
  if (bumperder == 1)
  {
    motion (-1, -1, 200, 100);
    delay (500); 
    motion (1, 1, 200, 200);
    delay (1500);
  }
  
  if((sensor1 >sensor3) && (sensor1 >4))
  {
    motion(-1, 1, 200, 100); 
  }
  
  else if(abs(sensor3-sensor4) < 100)
  {
    motion(-1, -1, 125, 125); 
  }
  
  else if (sensor3 > sensor4)
  {
    motion (-1, 0, velocidad, velocidad); 
  }
  else if (sensor3 < sensor4)
  {
     motion (0, -1, velocidad, velocidad); 
  }
  
  
}

void motion (int left, int right,int pwmL, int pwmR)
{
  if(pwmL <= 0) pwmL = 0;
  if(pwmR <= 0) pwmR = 0;
  if(pwmL > 255) pwmL = 255;
  if(pwmR > 255) pwmR = 255;
  
 if (left == 0)
 {
  analogWrite(5, 0);
  analogWrite(6, 0);
  //digitalWrite (5, LOW);
  //digitalWrite (6, LOW);  
 }
 if (left == 1)
 {
  analogWrite(6, 0);
  analogWrite(5, pwmL);
 }
 if (left == -1)
 {
  analogWrite(5, 0);
  analogWrite(6, pwmL);
 }

 if (right == 0)
 {
  analogWrite(10, 0);
  analogWrite(9, 0);
 }
 if (right == 1)
 {
  analogWrite(9, 0);
  analogWrite(10, pwmL);
 }
 if (right == -1)
 {
  analogWrite(10, 0);
  analogWrite(9, pwmL);
 }
}
