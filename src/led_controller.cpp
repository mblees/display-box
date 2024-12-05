#include "main.h" // included for LED_AMOUNT

volatile uint8_t led_data[LED_AMOUNT][3];
uint32_t Wheel(byte WheelPos);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_AMOUNT, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);
static uint8_t mode = 0;

void led_controller_init()
{
    for (int i = 0; i < LED_AMOUNT; i++)
    {
        led_data[i][0] = 0;
        led_data[i][1] = 255;
        led_data[i][2] = 0;
    }

    pinMode(LED_DATA_PIN, OUTPUT);
    strip.begin();
    strip.setBrightness(187);
}

void led_controller_do_work()
{
    static uint16_t offset = 0;
    offset = (offset + 1) % 256;

    for (uint16_t led = 0; led < LED_AMOUNT; led++)
    {
        switch (mode)
        {
        
        case 0:
            led_data[led][0] = 255;
            led_data[led][1] = 78;
            led_data[led][2] = 3;
            break;

        case 1:
            led_data[led][0] = 0;
            led_data[led][1] = 255;
            led_data[led][2] = 0;
            break;
        case 2:
            led_data[led][0] = 255;
            led_data[led][1] = 255;
            led_data[led][2] = 255;
            break;
        case 3:
            led_data[led][0] = 120;
            led_data[led][1] = 10;
            led_data[led][2] = 40;
            break;
        default:
            break;
        }

        if(mode == 4)
        {
            strip.setPixelColor(led, Wheel(((led * 256 / strip.numPixels()) + offset) & 255)); // rainbow
        }
        else
        {
            strip.setPixelColor(led, strip.Color(led_data[led][0], led_data[led][1], led_data[led][2]));
        }
    }

    strip.show();
    delay(10);
}

uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void set_mode(uint8_t new_mode)
{
    if (mode < 4)
    {
        mode = new_mode;
    }
    else
    {
        mode = 0;
    }
}


uint8_t get_mode()
{
    return mode;
}

void set_brightness(uint8_t brightness)
{
    strip.setBrightness(brightness);
}