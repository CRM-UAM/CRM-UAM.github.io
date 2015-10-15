/*
  Programa de prueba para el HKTR-9000 (prototipos)
  
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

int velocidad = 255/2; // Variable usada para la prueba de los motores

// --- SENSORES DE LINEA ---

// Funcion de inicializacion de pines
void inicia_pines_sensor_linea() {
  // Esto es necesario para leer los pines como digitales, en vez de como analogicos
  
  // ---> Aqui debe ir la inicializacion como entrada de los pines del sensor de linea
  
}


// --- MOTORES ---

// Funcion para la inicializacion de los pines como salidas
void inicia_pines_driver_motores() {
  // Inicia los pines como salidas
  
  // ---> Aqui debe ir la inicializacion como entrada de los pines del driver L298 de los motores
  
  // ---> Se les debe poner todos a 0
}

// Funciones para el control de los motores
// Toman un parametro que va de -255 a 255 que indica la velocidad y direccion de rotacion
//
// -255 == retroceder a maxima velocidad
//   0  == apagado
// +255 == avanzar a maxima velocidad
void motor_izq(int velocidad) {
  
  // ---> Aqui debe ir el codigo de control del motor izquierdo
  // ---> Revisar la hoja tecnica del CRM-Shield para mas informacion
  
}

// Lo mismo pero para el motor derecho
void motor_der(int velocidad) {
  
  // ---> Aqui debe ir el codigo de control del motor izquierdo
  // ---> Revisar la hoja tecnica del CRM-Shield para mas informacion
  
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
  
  // ---> Implementar la funcion de ruta
  
}

void setup() {                
  // Inicializacion de los pines
  inicia_pines_driver_motores();
  inicia_pines_sensor_linea();
  // ---> El pin 13 tiene un LED conectado, lo iniciamos como salida
  // No es necesario iniciar los pines de los LDR, ya que los leeremos como analogicos
  
  // Espera de 5 segundos antes de empezar a moverse
  // Asi evitamos que el robot se mueva al conectar el USB para la programacion
  delay(5000);
  
  // ---> Inicializacion del puerto serie
  
  
  // ---> Encendemos el LED para ver que se esta ejecutando el programa
  
  
  // -- Programa de prueba de todos los componentes:
  // Motores:
  
  // ---> Implementar las acciones descritas:
  
  // 1) El robot debe ir recto
  // Durante un segundo
  
  // 2) El robot debe quedarse parado
  // Durante un segundo
  
  // 3) La rueda derecha debe avanzar, con la izquierda parada
  // Durante un segundo
  
  // 4) El robot debe quedarse parado
  // Durante un segundo
  
  // 5) La rueda izquierda debe avanzar y la derecha retroceder
  // Durante un segundo
  
  // 6) El robot debe quedarse parado
  // Ya no deberia moverse mas lo que queda de codigo
  
}

void loop() {
  int ldr_izq_val, ldr_der_val;
  int ir_1, ir_2, ir_3, ir_4;
  
  // Lectura de los valores analogicos de los sensores LDR
  
  
  // Lectura de los valores digitales de los sensores CNY70
  
  
  // Enviamos por puerto serie las lecturas:
  // Sensores LDR
  
  
  // Sensores CNY70
  
  
  delay(100); // Manda las medidas por el puerto serie cada decima de segundo
}
