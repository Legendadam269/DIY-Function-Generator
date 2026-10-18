#include <AD9833.h>

// --- Pin Definitions ---
#define FSYNC 10
#define BUTTON_PIN 4
#define ENCODER_DT 3
#define ENCODER_CLK 2

// --- Object ---
AD9833 sigGen(FSYNC);

// --- Variables ---
unsigned long frequency = 1000;   // Hz
byte currentMode = 0;             // 0 = sine, 1 = triangle, 2 = square
int lastEncoderState;
bool updateSerial = false;

// --- Setup ---
void setup() {
  Serial.begin(9600);
  Serial.println("Signal Generator Started");

  // Initialize AD9833
  sigGen.begin();
  sigGen.reset();
  sigGen.setFrequency(frequency);
  sigGen.setWave(AD9833_SINE);

  // Encoder pins
  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_DT, INPUT_PULLUP);
  lastEncoderState = digitalRead(ENCODER_CLK);

  // Button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  serialStatus();   // Print initial status
}

// --- Main Loop ---
void loop() {
  // Handle encoder rotation
  int currentState = digitalRead(ENCODER_CLK);
  if (currentState != lastEncoderState) {
    if (digitalRead(ENCODER_DT) != currentState) {
      frequency += 100;   // Clockwise
    } 
    else if (frequency > 100) {
      frequency -= 100;   // Counter-clockwise
    }
    sigGen.setFrequency(frequency);
    updateSerial = true;
  }
  lastEncoderState = currentState;

  // Handle button press to switch waveform
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(200); // Debounce
    currentMode = (currentMode + 1) % 3;
    setWaveform();
    updateSerial = true;
    while (digitalRead(BUTTON_PIN) == LOW); // Wait for release
  }

  if (updateSerial) {
    serialStatus();
    updateSerial = false;
  }
}

// --- Print to Serial Monitor ---
void serialStatus() {
  Serial.print("Frequency: ");
  Serial.print(frequency);
  Serial.print(" Hz | Waveform: ");

  if (currentMode == 0) Serial.println("SINE");
  else if (currentMode == 1) Serial.println("TRIANGLE");
  else Serial.println("SQUARE");
}

// --- Change waveform ---
void setWaveform() {
  switch (currentMode) {
    case 0:
      sigGen.setWave(AD9833_SINE);
      break;
    case 1:
      sigGen.setWave(AD9833_TRIANGLE);
      break;
    case 2:
      sigGen.setWave(AD9833_SQUARE1);
      break;
  }
}
