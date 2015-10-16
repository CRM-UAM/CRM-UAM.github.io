// ------------- ULTRASONIDOS ---------------
// Basado en la libreria para el sensor BAT creada por Robi.Wang
void inicia_pines_ultrasonidos(int trigger, int echo) {
  // Configura el pin de trigger como salida, y el pin de echo como entrada
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}
int mide_distancia_ultrasonidos(int trigger, int echo) {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH); // Pone el pin de trigger a HIGH durante mas de 10us
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long microseconds = pulseIn(echo, HIGH, 20000); // Mide la duracion del pulso resultante (tiempo que tarda en regresar el sonido)
  return microseconds / 29 / 2;
}
// !------------ ULTRASONIDOS --------------!

void setup(){
  inicia_pines_ultrasonidos(8, 9); // Inicia los pines 6 (trigger) y 7 (echo) de un ultrasonidos
  Serial.begin(9600); // Inicia el puerto serie
  Serial.print("Prueba de ultrasonidos\n");
}
 
void loop(){
  // Lee la distancia medida por el sensor conectado a los pines 8 (trigger) y 9 (echo)
  int distancia_cm = mide_distancia_ultrasonidos(8, 9);
  Serial.print("Distancia = ");
  Serial.print("\t"); // Imprime tabulador
  Serial.print(distancia_cm); // Muestra distancia medida
  Serial.print("\n"); // Imprime salto de linea
  
  delay(100);
}

