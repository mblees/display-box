#ifndef KY040_H
#define KY040_H

#include <Arduino.h>

#define KY040_CLK_PIN 32
#define KY040_DT_PIN 25
#define KY040_SW_PIN 33

void init_KY040();
int getEncoderPosition();
bool isButtonPressed();

#endif // KY-040_H
