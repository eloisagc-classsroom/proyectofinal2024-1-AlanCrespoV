#include <LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Definir los pines análogos donde están conectados los fototransistores
const int pinFototransistor[] = {A5, A4, A3, A2, A1, A0};

// Variables para almacenar los valores leídos
int valoresLuz[6];
bool pin_detectado[6] = {false, false, false, false, false, false};
int valoresLuzPrevios[6] = {1023, 1023, 1023, 1023, 1023, 1023}; // Inicializados a 1023 para asegurar que se impriman al inicio
int monedas_contadas = 0;
// Variables para el conteo de monedas
int monedasDe050 = 0;
int monedasDe1 = 0;
int monedasDe2 = 0;
int monedasDe5 = 0;
int monedasDe10 = 0;

//Variable servo
Servo serv; 
// Estado del sistema
bool monedaEnSistema = false;

// Pin para el rotomotor
const int pinRotomotor = 13;

void setup() {
  // Iniciar comunicación serial
  Serial.begin(9600);

  // Iniciar el LCD
  lcd.begin(16, 2);

  //Iniciar servo
  serv.attach(8);
  serv.write(0);
  // Configurar los pines como entradas
  for (int i = 0; i < 6; i++) {
    pinMode(pinFototransistor[i], INPUT);
  }

  // Configurar el pin del rotomotor como salida
  pinMode(pinRotomotor, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Inserte sus ");
  lcd.setCursor(0, 1);
  lcd.print("monedas :D");
}

void loop() {
  // Leer los valores de los fototransistores
  bool imprimir = false;
  for (int i = 0; i < 6; i++) {
    valoresLuz[i] = analogRead(pinFototransistor[i]);
    if (valoresLuz[i] < 900 && valoresLuz[i] != valoresLuzPrevios[i]) {
      imprimir = true;
      pin_detectado[i] = true;
    }
  }

  // Detectar entrada de nueva moneda
  if (valoresLuz[5] < 900 && !monedaEnSistema) {
    monedaEnSistema = true;
  }

  // Detectar salida de la moneda
  if (valoresLuz[0] < 900 && monedaEnSistema) {
    monedas_contadas++;
    // Determinar el valor de la moneda y accionar el rotomotor
    if (pin_detectado[4]) {
      monedasDe10++;
      moverRotomotor(5); // Mover a la posición para 10 pesos
    } else if (pin_detectado[3]) {
      monedasDe5++;
      moverRotomotor(4); // Mover a la posición para 5 pesos
    } else if (pin_detectado[2]) {
      monedasDe2++;
      moverRotomotor(3); // Mover a la posición para 2 pesos
    } else if (pin_detectado[1]) {
      monedasDe1++;
      moverRotomotor(2); // Mover a la posición para 1 peso
    } else {
      monedasDe050++;
      moverRotomotor(1); // Mover a la posición para 0.50 pesos
    }

    // Imprimir el conteo de monedas en la consola serial
    Serial.println("Cantidad de monedas:");
    Serial.print("0.50: ");
    Serial.println(monedasDe050);
    Serial.print("1: ");
    Serial.println(monedasDe1);
    Serial.print("2: ");
    Serial.println(monedasDe2);
    Serial.print("5: ");
    Serial.println(monedasDe5);
    Serial.print("10: ");
    Serial.println(monedasDe10);
    
    // Mostrar el total de dinero en la LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Monedas: ");
    lcd.print(monedas_contadas);
    lcd.setCursor(0, 1);
    float total = monedasDe050 * 0.5 + monedasDe1 + monedasDe2 * 2 + monedasDe5 * 5 + monedasDe10 * 10;
    lcd.print("Total: $");
    lcd.print(total);
    delay(2000); // Esperar un poco para que el texto sea legible
    
    // Resetear estado
    monedaEnSistema = false;
    for (int i = 0; i < 6; i++) {
      pin_detectado[i] = false;
    }
  }

  // Actualizar los valores previos
  for (int i = 0; i < 6; i++) {
    valoresLuzPrevios[i] = valoresLuz[i];
  }
}

// Función para mover el rotomotor a la posición especificada
void moverRotomotor(int posicion) {
  // Suponer que cada posición corresponde a un tiempo diferente de activación
  // Ajusta los tiempos según sea necesario para tu sistema
  int tiempoActivacion = 0;
  switch (posicion) {
    case 1: // 0.50 pesos
      serv.write(0);
      break;
    case 2: // 1 peso
      serv.write(36);
      break;
    case 3: // 2 pesos
      serv.write(72);
      break;
    case 4: // 5 pesos
      serv.write(108);
      break;
    case 5: // 10 pesos
      serv.write(144);
      break;
  }
}
