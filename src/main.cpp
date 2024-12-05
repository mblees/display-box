#include "main.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial connected");

  // init_web_server();
  init_KY040();
  led_controller_init();
}

void loop()
{
  uint8_t mode = get_mode();
  set_brightness(getEncoderPosition());

  if (isButtonPressed())
  {
    if (mode != 4)
    {
      set_mode(mode + 1);
    }
    else
    {
      set_mode(0);
    }
  }

if(isButtonHeld3Seconds()){
  set_mode(4);
}
  led_controller_do_work();
  // web_server_do_work();
}