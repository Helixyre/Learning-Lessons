#include <Arduino.h>
#include <Freenove_WS2812_Lib_for_ESP32.h>

#define LEDS_COUNT  8
#define LEDS_PIN    2
#define CHANNEL     0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

void setup() {
	Serial.begin(115200);
	delay(50);
	Serial.println("WS2812 diag: set all pixels at once");
	if (!strip.begin()) {
		Serial.println("strip.begin() FAILED");
		while (1) delay(1000);
	}
	strip.setBrightness(30); // low power for safety

	// set all pixels at once (one show())
	uint8_t colors[LEDS_COUNT][3] = {
		{255,0,0},   // 1 red
		{0,255,0},   // 2 green
		{0,0,255},   // 3 blue
		{255,255,0}, // 4 yellow
		{255,0,255}, // 5 magenta
		{0,255,255}, // 6 cyan
		{255,255,255},// 7 white
		{128,64,0}   // 8 orange
	};

	for (int i = 0; i < LEDS_COUNT; i++) {
		strip.setLedColorData(i, colors[i][0], colors[i][1], colors[i][2]);
	}
	strip.show(); // send once
	Serial.println("Colors sent once. Observe LEDs.");
}

void loop() {
	// keep steady for observation
	delay(1000);
}