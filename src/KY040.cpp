#include "KY040.h"

#include "KY040.h"

// Globale Variablen zum Speichern des Zustands
volatile int encoderPos = 187;
int lastClkState;
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Entprellzeit

// Interrupt-Service-Routine (ISR) zum Verarbeiten von Drehungen
void IRAM_ATTR updateEncoder()
{
    int clkState = digitalRead(KY040_CLK_PIN);
    int dtState = digitalRead(KY040_DT_PIN);

    // Prüfen, ob sich der Encoder gedreht hat
    if (clkState != lastClkState)
    {
        if (dtState != clkState)
        {
            if (encoderPos < 255)
            {
                encoderPos += 8;
                if(encoderPos > 255)
                {
                    encoderPos = 255;
                }
            }
        }
        else
        {
            if (encoderPos > 0)
            {
                encoderPos -= 8;
                if(encoderPos < 0)
                {
                    encoderPos = 0;
                }
            }
        }
    }
    lastClkState = clkState;
}

// Initialisieren der KY-040 Pins und des Interrupts
void init_KY040()
{
    pinMode(KY040_CLK_PIN, INPUT);
    pinMode(KY040_DT_PIN, INPUT);
    pinMode(KY040_SW_PIN, INPUT_PULLUP); // Button mit Pullup-Widerstand

    lastClkState = digitalRead(KY040_CLK_PIN);

    // Attach interrupt für den CLK-Pin
    attachInterrupt(digitalPinToInterrupt(KY040_CLK_PIN), updateEncoder, CHANGE);
}

// Funktion zum Lesen der Position des Encoders
int getEncoderPosition()
{
    return encoderPos;
}

// Funktion zum Überprüfen des Button-Zustands
bool isButtonPressed()
{
    int reading = digitalRead(KY040_SW_PIN);

    // Entprellen
    if (reading != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        // Button-Zustand hat sich geändert
        if (reading != buttonState)
        {
            buttonState = reading;

            if (buttonState == LOW)
            {
                lastButtonState = reading;
                return true; // Button wurde gedrückt
            }
        }
    }

    lastButtonState = reading;
    return false;
}
