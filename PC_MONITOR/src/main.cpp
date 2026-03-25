#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- NUEVA CONFIGURACIÓN DE PINES ---
#define BTN_UP 27    // Subir scroll
#define BTN_DOWN 32  // Bajar scroll

// Variables de datos
int cpu = 0, ram = 0, disco = 0, temp = 0;
long red = 0;
int pagina = 0;

void dibujarPagina1();
void dibujarPagina2();

void setup() {
  Serial.begin(115200);
  
  // Configuración de botones con resistencia interna
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(25, 25);
  display.println("SISTEMA OK");
  display.setCursor(15, 40);
  display.println("ESPERANDO PC...");
  display.display();
}

void loop() {
  // 1. LECTURA DE DATOS (Protocolo: C:xx,R:xx,D:xx,N:xxxx,T:xx\n)
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    
    if (data.startsWith("C:")) {
      int rIdx = data.indexOf(",R:");
      int dIdx = data.indexOf(",D:");
      int nIdx = data.indexOf(",N:");
      int tIdx = data.indexOf(",T:");

      // Extracción segura de valores
      cpu   = data.substring(2, rIdx).toInt();
      ram   = data.substring(rIdx + 3, dIdx).toInt();
      disco = data.substring(dIdx + 3, nIdx).toInt();
      red   = data.substring(nIdx + 3, tIdx).toInt();
      temp  = data.substring(tIdx + 3).toInt();
    }
  }

  // 2. NAVEGACIÓN CON LOS NUEVOS PINES (27 y 32)
  // Botón Bajar (Pin 32)
  if (digitalRead(BTN_DOWN) == LOW) {
    delay(50); // Debounce
    if (digitalRead(BTN_DOWN) == LOW) {
      pagina++;
      if (pagina > 1) pagina = 0; // Ciclo entre páginas
      while(digitalRead(BTN_DOWN) == LOW); // Esperar a que suelte
    }
  }

  // Botón Subir (Pin 27)
  if (digitalRead(BTN_UP) == LOW) {
    delay(50); // Debounce
    if (digitalRead(BTN_UP) == LOW) {
      pagina--;
      if (pagina < 0) pagina = 1; // Ciclo inverso
      while(digitalRead(BTN_UP) == LOW); // Esperar a que suelte
    }
  }

  // 3. DIBUJAR INTERFAZ
  display.clearDisplay();
  
  // Encabezado
  display.setTextSize(1);
  display.setCursor(35, 0);
  display.print("PC MONITOR");
  display.drawFastHLine(0, 10, 128, WHITE);

  if (pagina == 0) {
    dibujarPagina1();
  } else {
    dibujarPagina2();
  }

  display.display();
}

void dibujarPagina1() {
  // --- SECCIÓN CPU ---
  display.setCursor(0, 18);
  display.print("CPU: "); display.print(cpu); display.print("%");
  if(temp > 0) { display.print(" | "); display.print(temp); display.print("C"); }
  
  display.drawRect(0, 28, 128, 8, WHITE);
  display.fillRect(0, 28, map(cpu, 0, 100, 0, 128), 8, WHITE);

  // --- SECCIÓN RAM ---
  display.setCursor(0, 42);
  display.print("RAM: "); display.print(ram); display.print("%");
  display.drawRect(0, 52, 128, 8, WHITE);
  display.fillRect(0, 52, map(ram, 0, 100, 0, 128), 8, WHITE);
}

void dibujarPagina2() {
  // --- SECCIÓN DISCO ---
  display.setCursor(0, 18);
  display.print("STORAGE (C:): "); display.print(disco); display.print("%");
  display.drawRect(0, 28, 128, 8, WHITE);
  display.fillRect(0, 28, map(disco, 0, 100, 0, 128), 8, WHITE);

  // --- SECCIÓN RED ---
  display.setCursor(0, 42);
  display.print("NET: "); 
  if (red > 1024) {
    display.print((float)red/1024, 1); display.print(" MB/s");
  } else {
    display.print(red); display.print(" KB/s");
  }

  // Decoración de barras de red
  for(int i=0; i<6; i++) {
    int h = (red > 0) ? (i+1)*2 : 1;
    display.fillRect(110 + (i*3), 60 - h, 2, h, WHITE);
  }
}