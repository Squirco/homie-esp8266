#include <Homie.h>

const int PIN_RELAY = 5;

HomieNode lightNode("light", "switch");

bool lightOnHandler(HomieRange range, String value) {
  if (value != "true" && value != "false") return false;

  bool on = (value == "true");
  digitalWrite(PIN_RELAY, on ? HIGH : LOW);
  Homie.setNodeProperty(lightNode, "on").send(value);
  Serial << "Light is " << (on ? "on" : "off") << endl;

  return true;
}

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);

  Homie_setFirmware("awesome-relay", "1.0.0");

  lightNode.advertise("on").settable(lightOnHandler);

  Homie.setup();
}

void loop() {
  Homie.loop();
}
