void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<8; i++) {
    digitalWrite(i, LOW);
    pinMode(i, OUTPUT);
  }
  for (int i=8; i<12; i++) {
    pinMode(i, INPUT_PULLUP);
    digitalWrite(i, HIGH);
  }
  // digitalWrite(12, LOW); // Reserved
  // pinMode(12, OUTPUT);
  digitalWrite(13, LOW); // Builtin LED
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  static int counter = 0;
  // digital 0-7: 8-bit counter pins
  for (int i=0; i<8; i++) {
    if (counter & (0x01<<i)) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
  // digital 8-11: one-hot in/out pins
  for (int i=0; i<4; i++) {
      pinMode(8 + i, INPUT_PULLUP);
  }
  //digitalWrite(8 + (counter % 4), HIGH);
  pinMode(8 + (counter % 4), OUTPUT); 

  // analog 0-5, digital 8-11: for plot
  for (int i=0; i<2; i++) {
    int pos = 0;
    char buf[8];
    for (int j=0; j<6; j++) {
      int raw = analogRead(j);
      int a = map(raw, 0, 1023, 0, 500);
      dtostrf(a/100.0 + (pos++)*5, 1, 2, buf);
      Serial.print(buf);
      Serial.print(",");
    }
    for (int j=0; j<4; j++) {
      int d = (digitalRead(j+8) + pos++) * 5;
      sprintf(buf, "%d,", d);
      Serial.print(buf);
    }
    Serial.print("\n");
    delay(20);
  }

  counter = (counter + 1) & 0xff;
}
