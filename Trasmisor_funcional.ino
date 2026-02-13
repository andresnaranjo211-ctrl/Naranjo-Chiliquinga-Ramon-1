#include <SPI.h>
#include <mcp_can.h>

#define CAN_CS 10

MCP_CAN CAN(CAN_CS);

// Sensores
const int SOUND_PIN = 3;
const int VIB_PIN   = 4;

void setup() {
  Serial.begin(115200);

  pinMode(SOUND_PIN, INPUT);
  pinMode(VIB_PIN, INPUT);

  // Inicializar CAN (16 MHz)
  while (CAN_OK != CAN.begin(MCP_ANY, CAN_250KBPS, MCP_8MHZ)) {
    Serial.println("Error iniciando CAN...");
    delay(500);
  }

  CAN.setMode(MCP_NORMAL);  // Poner en modo normal

  Serial.println("Transmisor CAN iniciado correctamente");
}

void loop() {

  bool soundState = digitalRead(SOUND_PIN);
  bool vibState   = digitalRead(VIB_PIN);

  unsigned char data[2];
  data[0] = soundState ? 1 : 0;
  data[1] = vibState ? 1 : 0;

  // Enviar mensaje con ID 0x100
  CAN.sendMsgBuf(0x100, 0, 2, data);

  Serial.print("Enviado -> Sonido: ");
  Serial.print(data[0]);
  Serial.print(" | Vibracion: ");
  Serial.println(data[1]);

  delay(100);
}
