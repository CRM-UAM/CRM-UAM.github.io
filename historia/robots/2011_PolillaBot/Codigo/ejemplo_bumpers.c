
 //Este es el codigo de un robot que he encontrado por internet.
 //Usa dos bumpers para evitar obstaculos, que es lo que queremos conseguir nosotros.
 
 //(sakul) 29-06-2011


int dirA = 12; // sentido
int dirB = 13;  // direccion 
int speedA = 10; // velocidad del motor
int speedB = 11; // parada o encendido de la dirección
int bumperI = 5; // bumper izquierdo
int bumperD = 4; // bumper derecho
int boton2 = 6; // boton 2 de la motorshield
int boton1 = 7; // boton 1 de la motorshield
 
// El robot va hacia atrás
void atras()
{
  digitalWrite (dirA, HIGH);
}
 
// El robot va hacia alante
void alante()
{
  digitalWrite (dirA, LOW);
}
 
// El robot tuerce a la izquierda
void izquierda()
{
  digitalWrite (dirB, LOW);
}
 
// El robot tuerce a la derecha
void derecha()
{
  digitalWrite (dirB, HIGH);
}
 
 
void setup() 
{
  // Configuración de los pines de la motorshield
  pinMode (dirA, OUTPUT); 
  pinMode (dirB, OUTPUT); 
  pinMode (speedA, OUTPUT); 
  pinMode (speedB, OUTPUT);
 
  // Configuración de los pines de los bumpers
  pinMode (bumperI, INPUT);
  pinMode (bumperD, INPUT);
 
  // Configuración de los botones de la motorshield
  pinMode (boton1, INPUT);
  pinMode (boton2, INPUT);
 
  // Configuración de las comunicaciones por bluetooth
  Serial.begin(9600);
}
 
 
void loop() 
{ 
  // Si se ha pulsado el boton de arranque
  if(digitalRead(boton1) == 0)
  {
    delay(200); // para evitar rebotes en el boton
    Serial.println("empiezo");  
    analogWrite(speedA, 100); // PWM a 100
  }
  // Si se ha pulsado el boton de parada
  else if(digitalRead(boton2) == 0)
  {
    delay(200); // para evitar rebotes en el boton
    Serial.println("termino");
    analogWrite(speedA, 0); // PWM a 0
  }  
  alante();
  // Si se ha detectado una colisión por el flanco derecho
  if(digitalRead(bumperD) == 0)
  {
    Serial.println("choque derecha");
    digitalWrite(speedB, HIGH); 
    // Va hacia atrás a la derecha durante 1 segundo    
    derecha();
    atras();
    delay(1000);
    // Va hacia alante a la izquierda durante medio segundo
    alante();
    izquierda();
    delay(500);
    digitalWrite(speedB, LOW); 
  }
  // Si se ha detectado una colisión por el flanco izquierdo
  else if(digitalRead(bumperI) == 0)
  {
    Serial.println("choque izquierda");
    digitalWrite(speedB, HIGH); 
    // Va hacia atrás a la izquierda durante 1 segundo
    izquierda();
    atras();
    delay(1000);
    // Va hacia alante a la derecha durante medio segundo    
    alante();
    derecha();
    delay(500);
    digitalWrite(speedB, LOW); 
  }
}
