#include "KY040.h"

// Globale Variablen zum Speichern des Zustands
volatile int encoderPos = 187;
int lastClkState;
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Entprellzeit

// Variable für 3-Sekunden-Button-Druck
bool buttonHeld3Seconds = false;
unsigned long buttonPressTime = 0; // Zeit, zu der der Button gedrückt wurde

// Interrupt-Service-Routine (ISR) zum Verarbeiten von Drehungen
void IRAM_ATTR updateEncoder() {
    int clkState = digitalRead(KY040_CLK_PIN);
    int dtState = digitalRead(KY040_DT_PIN);

    if (clkState != lastClkState) {
        if (dtState != clkState) {
            if (encoderPos < 255) {
                encoderPos += 8;
                if (encoderPos > 255) {
                    encoderPos = 255;
                }
            }
        } else {
            if (encoderPos > 0) {
                encoderPos -= 8;
                if (encoderPos < 0) {
                    encoderPos = 0;
                }
            }
        }
    }
    lastClkState = clkState;
}

// Initialisieren der KY-040 Pins und des Interrupts
void init_KY040() {
    pinMode(KY040_CLK_PIN, INPUT);
    pinMode(KY040_DT_PIN, INPUT);
    pinMode(KY040_SW_PIN, INPUT_PULLUP); // Button mit Pullup-Widerstand

    lastClkState = digitalRead(KY040_CLK_PIN);
    attachInterrupt(digitalPinToInterrupt(KY040_CLK_PIN), updateEncoder, CHANGE);
}

// Funktion zum Lesen der Position des Encoders
int getEncoderPosition() {
    return encoderPos;
}

// Funktion zum Überprüfen des Button-Zustands
bool isButtonPressed() {
    int reading = digitalRead(KY040_SW_PIN);

    // Entprellen
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
        buttonPressTime = millis(); // Startzeit zurücksetzen
        buttonHeld3Seconds = false; // Status zurücksetzen
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        // Button-Zustand hat sich geändert
        if (reading != buttonState) {
            buttonState = reading;

            if (buttonState == LOW) {
                // Button wurde gedrückt
                return true;
            }
        }
    }

    // Überprüfen, ob der Button 3 Sekunden gedrückt gehalten wurde
    if (buttonState == LOW) {
        if ((millis() - buttonPressTime) >= 3000) {
            buttonHeld3Seconds = true;
        }
    } else {
        buttonPressTime = millis(); // Zurücksetzen, wenn Button losgelassen wird
        buttonHeld3Seconds = false; // Zurücksetzen
    }

    lastButtonState = reading;
    return false;
}

// Funktion zum Abrufen des 3-Sekunden-Status
bool isButtonHeld3Seconds() {
    return buttonHeld3Seconds;
}
