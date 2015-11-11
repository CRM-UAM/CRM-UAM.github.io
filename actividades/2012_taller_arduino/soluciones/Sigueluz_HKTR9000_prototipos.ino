/*
  Codigo de sigueluz para el HKTR-9000 (prototipos)
  
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

int velocidad = 255/3; // Variable usada para la prueba de los motores

// --- SENSORES DE LINEA ---

// Funcion de inicializacion de pines
void inicia_pines_sensor_linea() {
  // Esto es necesario para leer los pines como digitales, en vez de como analogicos
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);
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

// -- EJERCICIO AVANZADO --
// Funcion para que el robot realice una ruta.
//
// Recibe como argumento una cadena de texto, en la que cada letra indica
// el movimiento que debe realizar el robot.
// Tambien recibe como argumento la velocidad a la que se movera.
//
// Ejemplo:
// ruta("frflfslbs", 50); // Realiza la ruta descrita a la velocidad 50
//
// f == forward
// b == backward
// r == right
// l == left
// s == stop
void ruta(char* texto, int vel) {
  while(*texto) { // Se recorre la cadena letra a letra
    switch(*texto) {
      case 'f'://forward
        motor_der(vel);
        motor_izq(vel);
        delay(500);
        break;
      
      case 'b'://backward
        motor_der(-vel);
        motor_izq(-vel);
        delay(500);
        break;
      
      case 'r'://right
        motor_der(0);
        motor_izq(vel);
        break;
      
      case 'l'://left
        motor_der(vel);
        motor_izq(0);
        break;
      
      case 's'://stop
        motor_der(0);
        motor_izq(0);
        break;
    }
    
    delay(300); // Espera por defecto 300 milisegundos para cada accion
                // Las funciones de avance y retroceso duran mas tiempo
                // que las funciones de giro.
    
    texto++; // Se recorre la cadena letra a letra
  }
}

void setup() {                
  // Inicializacion de los pines
  inicia_pines_driver_motores();
  inicia_pines_sensor_linea();
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
  int ldr_izq_val, ldr_der_val;
  
  // Lectura de los valores analogicos de los sensores LDR
  ldr_izq_val = analogRead(LDR_IZQ);
  ldr_der_val = analogRead(LDR_DER);
  
  // Enviamos por puerto serie las lecturas
  // Sensores LDR
  Serial.print("LDR_IZQ = ");
  Serial.print(ldr_izq_val);
  Serial.print("\t LDR_DER = ");
  Serial.println(ldr_der_val);
  
  // ---> Implementar un codigo que permita seguir la luz al robot
    
  delay(100); // Refresca los valores cada 100 milisegundos
}
