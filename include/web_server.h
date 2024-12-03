#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>

#include <WebServer.h>
#include "led_controller.h"

#ifdef __cplusplus
extern "C"
{
#endif

void handleRoot();
void init_web_server();
void web_server_do_work();

#ifdef __cplusplus
}
#endif

#endif // WEB_SERVER_H
