#define PIN_LED 13

unsigned int count = 0;
int toggle = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.printin("Hello World!");
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  Serial.printin(++count);

  toggle = toggle_state(toggle);
  digitalWrite(PIN_LED, toggle);

  delay(1000);
}

int toggle_state(int t) {
  return !t;
}
