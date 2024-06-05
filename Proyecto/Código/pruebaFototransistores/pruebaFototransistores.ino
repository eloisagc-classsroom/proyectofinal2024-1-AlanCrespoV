// Definición de los pines de los fototransistores
const int fototransistor1 = 13;
const int fototransistor2 = 12;
const int fototransistor3 = 11;
const int fototransistor4 = 10;
const int fototransistor5 = 9;
const int fototransistor6 = 8;

void setup() {
  // Inicialización de la comunicación serial
  Serial.begin(9600);

  // Configuración de los pines de los fototransistores como entrada
  pinMode(fototransistor1, INPUT);
  pinMode(fototransistor2, INPUT);
  pinMode(fototransistor3, INPUT);
  pinMode(fototransistor4, INPUT);
  pinMode(fototransistor5, INPUT);
  pinMode(fototransistor6, INPUT);
}

void loop() {
  // Leer el estado de cada fototransistor
  int estadoFototransistor1 = digitalRead(fototransistor1);
  int estadoFototransistor2 = digitalRead(fototransistor2);
  int estadoFototransistor3 = digitalRead(fototransistor3);
  int estadoFototransistor4 = digitalRead(fototransistor4);
  int estadoFototransistor5 = digitalRead(fototransistor5);
  int estadoFototransistor6 = digitalRead(fototransistor6);

  // Imprimir el estado de cada fototransistor en el monitor serial
  Serial.print("Fototransistor 1: ");
  Serial.println(estadoFototransistor1 == HIGH ? "Recibiendo luz" : "No recibiendo luz");

  Serial.print("Fototransistor 2: ");
  Serial.println(estadoFototransistor2 == HIGH ? "Recibiendo luz" : "No recibiendo luz");

  Serial.print("Fototransistor 3: ");
  Serial.println(estadoFototransistor3 == HIGH ? "Recibiendo luz" : "No recibiendo luz");

  Serial.print("Fototransistor 4: ");
  Serial.println(estadoFototransistor4 == HIGH ? "Recibiendo luz" : "No recibiendo luz");

  Serial.print("Fototransistor 5: ");
  Serial.println(estadoFototransistor5 == HIGH ? "Recibiendo luz" : "No recibiendo luz");

  Serial.print("Fototransistor 6: ");
  Serial.println(estadoFototransistor6 == HIGH ? "Recibiendo luz" : "No recibiendo luz");

  // Esperar un segundo antes de la próxima lectura
  delay(1000);
}
