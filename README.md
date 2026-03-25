# 🖥️ ESP32 PC Resource Monitor (v2.0)

Este proyecto permite visualizar la telemetría de tu PC en tiempo real usando un ESP32 y una pantalla OLED SSD1306. El sistema detecta automáticamente el hardware y permite navegar por los datos mediante botones físicos.

---

## 🛠️ 1. Conexiones de Hardware

| Componente | Pin ESP32 | Función |
| :--- | :--- | :--- |
| OLED SDA | GPIO 21 | Datos I2C |
| OLED SCL | GPIO 22 | Reloj I2C |
| Botón UP | GPIO 27 | Subir / Anterior Página |
| Botón DOWN | GPIO 32 | Bajar / Siguiente Página |
| VCC / GND | 3.3V / GND | Alimentación (3.3V recomendado) |

Nota: Conecta un extremo del botón al pin del ESP32 y el otro a GND. El código usa INPUT_PULLUP interno.

---

## 📥 2. Instalación de Python en Windows

1. Descargar Python: Ve a python.org y descarga la última versión.
2. Instalación Crítica: Al ejecutar el instalador, DEBES marcar la casilla "Add Python to PATH".
3. Instalar Dependencias: Abre una terminal (CMD o PowerShell) y ejecuta:
   pip install psutil pyserial

---

## 🔌 3. Configuración del ESP32 (PlatformIO)

1. Abre tu proyecto en VS Code con la extensión PlatformIO.
2. En tu archivo platformio.ini, añade las librerías necesarias:
   lib_deps =
       adafruit/Adafruit SSD1306 @ ^2.5.13
       adafruit/Adafruit GFX Library @ ^1.11.11
3. Copia el código fuente al archivo src/main.cpp y cárgalo a la placa usando la flecha derecha (->) en la barra inferior de VS Code.

---

## 🚀 4. Cómo Ejecutar el Monitor

1. Conecta el ESP32 a la PC mediante el cable USB.
2. IMPORTANTE: Cierra el Monitor Serial de VS Code. Si el puerto COM está ocupado, el script de Python no podrá conectarse.
3. Abre una terminal en la carpeta donde guardaste el script main.py y ejecútalo:
   python main.py

---

## 🤖 5. Automatización (Inicio con Windows)

Si quieres que el monitor arranque solo al encender la PC sin ver ventanas de terminal:

1. Presiona Win + R, escribe shell:startup y pulsa Enter.
2. Crea un archivo nuevo en esa carpeta llamado lanzador.vbs.
3. Haz clic derecho sobre el archivo, elige "Editar" y pega lo siguiente:
   Set WshShell = CreateObject("WScript.Shell")
   ' REEMPLAZA LA RUTA DE ABAJO POR LA TUYA:
   WshShell.Run "python C:\Ruta\A\Tu\Carpeta\main.py", 0
   Set WshShell = Nothing
4. Guarda los cambios. Ahora, cada vez que inicies sesión, el monitor se activará automáticamente.

---

## 📸 Demostración en Video (Reel)

Haz clic en la imagen de abajo para ver el monitor en acción:

[![Ver el Reel en Instagram](https://img.shields.io/badge/Ver_Video_en_Instagram-E4405F?style=for-the-badge&logo=instagram&logoColor=white)](https://www.instagram.com/reel/DWN8WFRDp_f/)

---

> **Nota:** En el video se aprecia la informacion del PC dentro de la pantalla oled del esp32.

---

## 👨‍💻 Autor
**Pepe Angell** *Ingeniería y Desarrollo de Sistemas Embebidos* [www.instagram.com/pepeangell y www.instagram.com/pepeangelll]

---
