/*
  Codigo del sensor de distancia por ultrasonidos para el HKTR-9000
  
  CRM-UAM
  Taller de iniciacion a la Robotica 2012
  Robot: HKTR-9000
    Carlos Garcia Saura
    Lucas Polo Lopez
    Miguel Gargallo Vazquez
    
  Mayo 2012
 */


// -- Definiciones de los pines

#define LED 13       // Pin para el LED

#define M_INPUT_1 9  // Pines para el driver de motores L298
#define M_INPUT_2 11
#define M_INPUT_3 10
#define M_INPUT_4 12
#define M_ENABLE_A 6
#define M_ENABLE_B 5

#define LDR_IZQ A5   // Pines para los sensores de luz LDR
#define LDR_DER A4

#define IR_1 A0      // Pines para los sensores de linea CNY70
#define IR_2 A1      // El IR_1 es el derecho, el IR_4 el izquierdo
#define IR_3 A2
#define IR_4 A3

#define PIN_ULTRASONIDOS_PW 2 // Pines para el sensor de ultrasonidos
#define PIN_ULTRASONIDOS_RX 3

// --- SENSOR DE ULTRASONIDOS ---

// Funcion de inicializacion de pines
void inicia_pines_sensor_ultrasonidos() {
  pinMode(PIN_ULTRASONIDOS_PW, INPUT);
  pinMode(PIN_ULTRASONIDOS_RX, OUTPUT);
  
  // El pin debe iniciarse a 0 para que el sensor no mida constantemente
  digitalWrite(PIN_ULTRASONIDOS_RX, LOW);
}

// Funcion que devuelve la distancia en centimetros leida por el sensor
int lee_distancia_ultrasonidos() {
  long pulso;
  
  // Se pone el pin RX a 1
  digitalWrite(PIN_ULTRASONIDOS_RX, HIGH);
  
  // Se recibe la medicion
  // La funcion pulseIn mide el tiempo en microsegundos que dura un pulso
  pulso = pulseIn(PIN_ULTRASONIDOS_PW, HIGH);
  
  // Se pone el pin RX a 0
  digitalWrite(PIN_ULTRASONIDOS_RX, LOW);
  
  // El resultado se devuelve convirtiendo la duracion del pulso a centimetros
  return pulso/57.874;
}

// --- MOTORES ---

// Funcion para la inicializacion de los pines como salidas
void inicia_pines_driver_motores() {
  // Inicia los pines como salidas
  pinMode(M_INPUT_1, OUTPUT);
  pinMode(M_INPUT_2, OUTPUT);
  pinMode(M_INPUT_3, OUTPUT);
  pinMode(M_INPUT_4, OUTPUT);
  pinMode(M_ENABLE_A, OUTPUT);
  pinMode(M_ENABLE_B, OUTPUT);
  
  // Los inicia apagados
  digitalWrite(M_INPUT_1, LOW);
  digitalWrite(M_INPUT_2, LOW);
  digitalWrite(M_INPUT_3, LOW);
  digitalWrite(M_INPUT_4, LOW);
  digitalWrite(M_ENABLE_A, LOW);
  digitalWrite(M_ENABLE_B, LOW);
}

// Funciones para el control de los motores
// Toman un parametro que va de -255 a 255 que indica la velocidad y direccion de rotacion
void motor_izq(int velocidad) {
  if(velocidad > 0) {// Hacia delante
    digitalWrite(M_INPUT_2, LOW);// Direccion de giro
    digitalWrite(M_INPUT_1, HIGH);
    
    analogWrite(M_ENABLE_A, velocidad);// Velocidad (siempre un parametro positivo para PWM)
    
  } else if(velocidad < 0) {// Hacia atras
    digitalWrite(M_INPUT_2, HIGH);// Direccion de giro
    digitalWrite(M_INPUT_1, LOW);
    
    analogWrite(M_ENABLE_A, -velocidad);// Velocidad (siempre un parametro positivo para PWM)
    
  } else {//Parado
      digitalWrite(M_ENABLE_A, LOW);// Motor apagado
  }
}

// Lo mismo pero para el motor derecho
void motor_der(int velocidad) {
  if(velocidad > 0) {// Hacia delante
    digitalWrite(M_INPUT_4, LOW);// Direccion de giro
    digitalWrite(M_INPUT_3, HIGH);
    
    analogWrite(M_ENABLE_B, velocidad);// Velocidad (siempre un parametro positivo para PWM)
    
  } else if(velocidad < 0) {//Hacia atras
    digitalWrite(M_INPUT_4, HIGH);// Direccion de giro
    digitalWrite(M_INPUT_3, LOW);
    
    analogWrite(M_ENABLE_B, -velocidad);// Velocidad (siempre un parametro positivo para PWM)
    
  } else {//Parado
      digitalWrite(M_ENABLE_B, LOW);// Motor apagado
  }
}

void setup() {                
  // Inicializacion de los pines
  inicia_pines_driver_motores();
  inicia_pines_sensor_ultrasonidos();
  pinMode(LED,OUTPUT); // El pin 13 tiene un LED conectado, lo iniciamos como salida
  // No es necesario iniciar los pines de los LDR, ya que los leeremos como analogicos
  
  // Espera de 5 segundos antes de empezar a moverse
  // Asi evitamos que el robot se mueva al conectar el USB para la programacion
  delay(5000);
  
  // Inicializacion del puerto serie
  Serial.begin(9600);
  
  // Encendemos el LED para ver que se esta ejecutando el programa
  digitalWrite(LED, HIGH);
}

void loop() {
  int distancia = lee_distancia_ultrasonidos();
  Serial.print("DISTANCIA = ");
  Serial.println(distancia);
  
  delay(500);
}
