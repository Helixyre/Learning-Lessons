#include <Arduino.h>
#include <ESP32PWM.h>
#include <math.h>

#define PIN_LED   2
#define CHN       0
#define FRQ       1000
#define PWM_BIT   8
#define BREATHING_SPEED 2.0

void setup() {
  ledcSetup(CHN, FRQ, PWM_BIT);
  ledcAttachPin(PIN_LED, CHN);
}

void loop() {
  float t = millis() / 1000.0;
  float brightness = pow(sin(t * BREATHING_SPEED), 2) * 255.0;
  ledcWrite(CHN, (int)brightness);
  delay(5);
}