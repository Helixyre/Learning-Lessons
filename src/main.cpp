#include <Arduino.h>

#define PIN_ANALOG_IN   4
#define PIN_LED         12
#define CHAN            0
#define LIGHT_MIN       372
#define LIGHT_MAX       2048

void setup() {
  Serial.begin(115200);
  // initialize LEDC: channel, frequency(Hz), resolution(bits)
  ledcSetup(CHAN, 1000, 12);
  ledcAttachPin(PIN_LED, CHAN);
}

void loop() {
  int adcVal = analogRead(PIN_ANALOG_IN); // read ADC
  int pwmVal = map(constrain(adcVal, LIGHT_MIN, LIGHT_MAX), LIGHT_MIN, LIGHT_MAX, 0, 4095);  // map to 12-bit range
  pwmVal = constrain(pwmVal, 0, 4095);
  // Use channel (CHAN) as first parameter. Passing the pin here caused "LEDC is not initialized" because
  // the wrong channel index was used.
  ledcWrite(CHAN, pwmVal);    // set the pulse width on the configured channel
  delay(10);
}