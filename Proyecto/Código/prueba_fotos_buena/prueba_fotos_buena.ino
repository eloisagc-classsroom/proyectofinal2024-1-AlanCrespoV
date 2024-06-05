// Definir los pines análogos donde están conectados los fototransistores
const int pinFototransistor[] = {A0, A1, A2, A3, A4, A5};

// Variables para almacenar los valores leídos
int valoresLuz[6];
int valoresLuzPrevios[6] = {1023, 1023, 1023, 1023, 1023, 1023}; // Inicializados a 1023 para asegurar que se impriman al inicio

void setup() {
  // Iniciar comunicación serial
  Serial.begin(9600);

  // Configurar los pines como entradas
  for (int i = 0; i < 6; i++) {
    pinMode(pinFototransistor[i], INPUT);
  }
}

void loop() {
  // Leer los valores de los fototransistores
  bool imprimir = false;
  for (int i = 0; i < 6; i++) {
    valoresLuz[i] = analogRead(pinFototransistor[i]);
    if (valoresLuz[i] < 900 && valoresLuz[i] != valoresLuzPrevios[i]) {
      imprimir = true;
    }
  }

  // Solo imprimir los valores si hay algún cambio y es menor a 800
  if (imprimir) {
    Serial.print("Valores de luz cambiados: ");
    for (int i = 0; i < 6; i++) {
      if (valoresLuz[i] < 900 && valoresLuz[i] != valoresLuzPrevios[i]) {
        Serial.print("A");
        Serial.print(i);
        Serial.print(": ");
        Serial.print(valoresLuz[i]);
        Serial.print(" ");
      }
      // Actualizar los valores previos
      valoresLuzPrevios[i] = valoresLuz[i];
    }
    Serial.println();
  }
}
