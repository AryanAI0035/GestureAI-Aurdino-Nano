#include "GestureModel.h"

// --- Input Pins (3 IR Sensors) ---
const int IR_UP = 2;
const int IR_DOWN = 3;
const int IR_LEFT = 4;

// --- Output Pins (LEDs: Red, Green, Red) ---
const int LED_RED_1 = 8;
const int LED_GREEN = 9;
const int LED_RED_2 = 10;

// Create the AI object
Eloquent::ML::Port::DecisionTree clf;

// 8 snapshots * 3 sensors = 24 data points
float features[24];

// Helper function to completely clear the AI's memory
void resetWindow() {
  for(int i = 0; i < 24; i++) {
    features[i] = 1; // 1 means empty/idle for IR sensors
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(IR_UP, INPUT);
  pinMode(IR_DOWN, INPUT);
  pinMode(IR_LEFT, INPUT);
  
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);

  resetWindow();
  
  Serial.println("AI Booted and Ready!");
  Serial.println("Waiting for ONE clean gesture...");
  Serial.println("-----------------------");
}

void loop() {
  // 1. Slide the window normally
  for (int i = 0; i < 21; i++) {
    features[i] = features[i + 3];
  }
  features[21] = digitalRead(IR_UP);
  features[22] = digitalRead(IR_DOWN);
  features[23] = digitalRead(IR_LEFT);
  
  // 2. Check if a gesture is STARTING
  int initial_prediction = clf.predict(features);
  
  // 3. ACTION LOGIC
  if (initial_prediction != 0) {
    
    // --- THE FIX: LET IT COOK ---
    // The AI just noticed a gesture starting. But we won't trust it yet!
    // We rapidly grab 3 more frames (300ms) to let the "Push In" fully develop.
    for(int wait = 0; wait < 3; wait++) {
      delay(100);
      
      // Slide and capture again
      for (int i = 0; i < 21; i++) {
        features[i] = features[i + 3];
      }
      features[21] = digitalRead(IR_UP);
      features[22] = digitalRead(IR_DOWN);
      features[23] = digitalRead(IR_LEFT);
    }

    // NOW we ask the AI to predict on the fully developed window!
    int final_prediction = clf.predict(features);

    // Fallback: If the hand moved too fast and it thinks it's Idle now, 
    // we use the initial guess.
    if (final_prediction == 0) {
      final_prediction = initial_prediction;
    }
    
    // 4. Fire the LEDs and print in ALL CAPS
    if (final_prediction == 1) {
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_RED_1, HIGH);
      Serial.println("PUSH IN");
    } 
    else if (final_prediction == 2) {
      digitalWrite(LED_RED_1, HIGH);
      Serial.println("SWIPE LEFT");
    } 
    else if (final_prediction == 3) {
      digitalWrite(LED_GREEN, HIGH);
      Serial.println("SWIPE RIGHT");
    }

    // The 10-Second Hard Freeze
    Serial.println("FREEZING FOR 5 SECONDS...");
    delay(5000); 

    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED_2, LOW);

    // FLUSH THE MEMORY
    resetWindow();
    
    Serial.println("READY FOR NEXT GESTURE.");
    Serial.println("-----------------------");
  }

  // Normal snapshot delay
  delay(100); 
}