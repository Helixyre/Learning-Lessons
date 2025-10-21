#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Configuration
#define PIN        2   // On ESP32, GPIO2 is used for data
#define NUMPIXELS  8   // Number of LEDs in your strip

// NeoPixel object
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Helper utilities
static inline void setAll(uint32_t color) {
    for (int i = 0; i < NUMPIXELS; ++i) pixels.setPixelColor(i, color);
}

static inline void clearAll() {
    pixels.clear();
    pixels.show();
}

// Light a quadrant (2 LEDs) green for the Xbox startup look
void xboxStartupSequence() {
    Serial.println("[XBOX] Startup sequence: rotating green quadrants");
    uint32_t green = pixels.Color(0, 200, 0);

    // rotate each quadrant (pairs of LEDs) several times
    for (int cycle = 0; cycle < 4; ++cycle) {
        for (int q = 0; q < 4; ++q) {
            pixels.clear();
            int a = q * 2;
            pixels.setPixelColor(a, green);
            pixels.setPixelColor(a + 1, green);
            pixels.show();
            delay(220);
        }
    }

    // brief full-green flash (boot OK)
    setAll(pixels.Color(0, 255, 0));
    pixels.show();
    delay(800);
    clearAll();
}

// Simulate the Red Ring of Death (RRoD)
void simulateRRoD() {
    Serial.println("[RRoD] Simulating Red Ring of Death");
    // Pulse red a few times (ramp up/down)
    for (int p = 0; p < 4; ++p) {
        for (int intensity = 0; intensity <= 200; intensity += 20) {
            setAll(pixels.Color(intensity, 0, 0));
            pixels.show();
            delay(25);
        }
        for (int intensity = 200; intensity >= 0; intensity -= 20) {
            setAll(pixels.Color(intensity, 0, 0));
            pixels.show();
            delay(25);
        }
    }

    // A few slow blinks then a steady red "dead" ring
    for (int i = 0; i < 4; ++i) {
        setAll(pixels.Color(200, 0, 0));
        pixels.show();
        delay(600);
        clearAll();
        delay(400);
    }

    // Final steady RRoD
    setAll(pixels.Color(200, 0, 0));
    pixels.show();
    Serial.println("[RRoD] Final steady red ring set");
}

void setup() {
    Serial.begin(115200);
    delay(50);
    pixels.begin();
    pixels.show(); // ensure off
    pixels.setBrightness(30); // safety: keep brightness low

    Serial.println("Starting simulated boot sequence...");

    // Xbox startup then immediate failure (RRoD)
    xboxStartupSequence();
    delay(300);
    simulateRRoD();

    Serial.println("Sequence complete. Device in final RRoD state.");
}

void loop() {
    // Stay in final RRoD state. If you want to replay, reset the board.
    delay(1000);
}