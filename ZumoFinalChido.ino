#define distanciaMaxima 70
// ----- Sensores --------------
const int sensor = A0;
// Detector Línea
int cny = 8;

int valorCNY = 0;
bool detenerAccion = false;  // Variable para detener toda acción si se detecta línea
unsigned long tiempoRetroceso = 0; // Almacena el tiempo de inicio del retroceso
const unsigned long duracionRetroceso = 300; // Tiempo de retroceso en milisegundos (1 segundo)

// ------ Motores -----------------
// Motor 1
int ENA = 3;  // PWMA --- Morado
int IN1 = 4;  // IN1 --- verde
int IN2 = 2;  // IN2 --- Amarillo
// Motor 2
int ENB = 9;  // PWMB ---- Morado
int IN3 = 5;  // BIN1 ---- Rojo
int IN4 = 6;  // BIN2 ---- Cafe

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(cny, INPUT);

  Serial.println("ROBOT PREPARADO...");
  delay(5000);
}

void loop() {
  float data = analogRead(sensor);
  valorCNY = digitalRead(cny);

  if (valorCNY != 0 && !detenerAccion) {  
    // Detecta la línea por primera vez y activa retroceso
    detenerAccion = true;
    tiempoRetroceso = millis(); // Guarda el tiempo de inicio de retroceso
    Serial.println("Línea detectada, iniciando retroceso de 1 segundo");
    Adelante();
  }

  if (detenerAccion) {
    // Si está en modo de retroceso, verifica si ha pasado 1 segundo
    if (millis() - tiempoRetroceso >= duracionRetroceso) {
      detenerAccion = false; // Termina el retroceso después de 1 segundo
      Izquierda(); // Detiene el robot después de retroceder
      Serial.println("Retroceso completo, regresando a acciones normales");
    }
  } else {
    // Lógica de combate normal si no se detecta línea
    if (data >= 350) {  // Detecta enemigo
      Serial.println("Atacando");
      Atras();
    } else {
      Serial.println("No se detecta enemigo, buscando");
      //Izquierda();
     Izquierda();
    }
  }
}

void Izquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 140);
}

void Adelante() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 200);
}

void Parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void Atras() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 250);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 250);
}

void AdelanteLento(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 150);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 150);
}
