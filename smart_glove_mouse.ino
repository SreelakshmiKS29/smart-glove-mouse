#include <BleMouse.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// ---------------- OBJECTS ----------------
BleMouse bleMouse("ESP32_Air2_Mouse", "Saniya", 100);
Adafruit_MPU6050 mpu;

// ---------------- FLEX PINS ----------------
// We only need 3 pins now!
#define FLEX_THUMB  34   // Scroll Clutch
#define FLEX_INDEX  35   // Left Click & Drag
#define FLEX_MIDDLE 32   // Right Click

// ---------------- VARIABLES ----------------
int threshold = 2100;

bool leftClicked = false;
bool rightClicked = false;

// smoothing variables
float smoothX = 0;
float smoothY = 0;
float alpha = 0.2;

// flex smoothing
int flexThumb = 2800, flexIndex = 2800, flexMiddle = 2800;

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);

  // Initialize only the 3 pins we are using
  pinMode(FLEX_THUMB, INPUT);
  pinMode(FLEX_INDEX, INPUT);
  pinMode(FLEX_MIDDLE, INPUT);

  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  bleMouse.begin();
  Serial.println("Bluetooth Mouse Ready! Pair your device.");
}

// ---------------- LOOP ----------------
void loop() {

  if (bleMouse.isConnected()) {

    // ---------- MPU6050 READING ----------
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float y = -g.gyro.y;
    float x = -g.gyro.x;

    // Apply math smoothing to the raw gyro data
    smoothX = alpha * x + (1 - alpha) * smoothX;
    smoothY = alpha * y + (1 - alpha) * smoothY;

    // Dead zone to prevent cursor jitter when your hand is still
    if (abs(smoothX) < 0.05) smoothX = 0;
    if (abs(smoothY) < 0.05) smoothY = 0;

    // ---------- FLEX SENSOR SMOOTHING & ANTI-CROSSTALK ----------
    flexThumb = 0.7 * flexThumb + 0.3 *
                analogRead(FLEX_THUMB);
    flexIndex = 0.7 * flexIndex + 0.3 *
                analogRead(FLEX_INDEX);
    flexMiddle = 0.7 * flexMiddle + 0.3 *
                 analogRead(FLEX_MIDDLE);

    // ---------- LEFT CLICK & DRAG (Index finger) ----------
    if (flexIndex < threshold && !leftClicked) {
      bleMouse.press(MOUSE_LEFT); // Press AND HOLD for easy dragging
      leftClicked = true;
    }
    if (flexIndex >= threshold && leftClicked) {
      bleMouse.release(MOUSE_LEFT);
      leftClicked = false;
    }

    // ---------- RIGHT CLICK (Middle finger) ----------
    if (flexMiddle < threshold && !rightClicked) {
      bleMouse.press(MOUSE_RIGHT);
      rightClicked = true;
    }
    if (flexMiddle >= threshold && rightClicked) {
      bleMouse.release(MOUSE_RIGHT);
      rightClicked = false;
    }

    // ---------- MOVEMENT & SCROLL CLUTCH (Thumb finger) ----------
    if (flexThumb < threshold) {
      // 1. SCROLL MODE (Thumb is bent)
      // The cursor freezes, and tilting your wrist up/down scrolls
      // the page
      if (smoothY > 0.05) {
        bleMouse.move(0, 0, 1);
        delay(40);
      }
      else if (smoothY < -0.05) {
        bleMouse.move(0, 0, -1);
        delay(40);
      }
    } else {
      // 2. NORMAL CURSOR MODE (Thumb is straight)
      // Move the mouse normally with 20x sensitivity
      bleMouse.move(smoothX * 20, smoothY * 20);
    }

    delay(10); // Standard stability delay
  }
}
