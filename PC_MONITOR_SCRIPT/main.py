import psutil
import serial
import serial.tools.list_ports
import time

def buscar_puerto_esp32():
    """Detecta automáticamente el ESP32 por su chip USB-Serial."""
    for p in serial.tools.list_ports.comports():
        if any(x in p.description for x in ["CP210", "CH340", "USB Serial"]):
            return p.device
    return None

def obtener_red():
    """Calcula KB/s de descarga."""
    n1 = psutil.net_io_counters().bytes_recv
    time.sleep(0.1)
    n2 = psutil.net_io_counters().bytes_recv
    return int((n2 - n1) / 10.24) # KB/s ajustado

print("🚀 MONITOR PRO: BUSCANDO ESP32...")

while True:
    puerto = buscar_puerto_esp32()
    if puerto:
        try:
            esp32 = serial.Serial(puerto, 115200, timeout=1)
            print(f"✅ Conectado en {puerto}")
            while True:
                cpu = int(psutil.cpu_percent())
                ram = int(psutil.virtual_memory().percent)
                disco = int(psutil.disk_usage('C:').percent)
                red = obtener_red()
                
                # Intentar temperatura (CoreTemp debe estar abierto en algunas PCs)
                temp = 0
                try:
                    t = psutil.sensors_temperatures()
                    if 'coretemp' in t: temp = int(t['coretemp'][0].current)
                except: temp = 0

                # CADENA EXACTA: C:xx,R:xx,D:xx,N:xxxx,T:xx\n
                mensaje = f"C:{cpu},R:{ram},D:{disco},N:{red},T:{temp}\n"
                esp32.write(mensaje.encode('utf-8'))
                
                print(f"Enviando: {mensaje.strip()}", end='\r')
                time.sleep(0.8) # Sincronizado con el ESP32
        except:
            print("\n🔌 Conexión perdida...")
            time.sleep(2)
    else:
        time.sleep(2)