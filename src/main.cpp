#include <Arduino.h>
#include <ESP32PWM.h>

void setColor(byte r, byte g, byte b);

const byte ledPins[] = {4, 2, 15};
const byte chns[] = {0, 1, 2};
int red, green, blue;

void setup() {
  for (int i = 0; i < 3; i++) {   // setup the pwm channels, 1KHz, 8bit
    ledcSetup(chns[i], 1000, 8);
    ledcAttachPin(ledPins[i], chns[i]);
  }
  randomSeed(analogRead(0));
}

void loop() {
  red = random(0, 256);
  green = random(0, 256);
  blue = random(0, 256);
  setColor(red, green, blue);
  delay(200);
}

// setColor: write PWM values to the 3 channels
void setColor(byte r, byte g, byte b) {
  // If using a common-anode LED, invert values (255 - value)
  ledcWrite(chns[0], 255 - r);
  ledcWrite(chns[1], 255 - g);
  ledcWrite(chns[2], 255 - b);
}