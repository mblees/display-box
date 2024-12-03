#include "web_server.h"

const char *ssid = "HarleyAnzeige";
const char *password = "HarleyAnzeige";

IPAddress local_IP(192, 168, 1, 1); // Set your desired IP address here
IPAddress gateway(192, 168, 1, 1);  // Set your gateway IP address here
IPAddress subnet(255, 255, 255, 0); // Set your subnet mask here

WebServer server(80);

static uint8_t brightness = 187;

void handleRoot();
void handleGreen();
void handleWhite();
void handlePink();
void handleRainbow();
void handleOrange();

void init_web_server()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_IP, gateway, subnet); // Configure static IP
    WiFi.softAP(ssid, password);

    // Print local IP address
    Serial.println();
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    server.on("/", handleRoot);
    server.on("/green", handleGreen);
    server.on("/orange", handleOrange);
    server.on("/white", handleWhite);
    server.on("/pink", handlePink);
    server.on("/rainbow", handleRainbow);
    server.begin();
}

void web_server_do_work()
{
    server.handleClient();
}

void handleRoot()
{
    String html = "<html><head>";
    html += "<style>";
    html += "html, body { height: 100%; margin: 0; }";
    html += "body { display: flex; flex-direction: column; justify-content: center; align-items: center; }";
    html += "form { width: 95%; height: 20%; margin: 10px 0; }";
    html += "button { width: 100%; height: 100%; font-size: 2em; }";
    html += "</style>";
    html += "</head><body>";
    html += "<form action='/green' method='get'><button type='submit'>Green</button></form>";
    html += "<form action='/orange' method='get'><button type='submit'>Orange</button></form>";
    html += "<form action='/white' method='get'><button type='submit'>White</button></form>";
    html += "<form action='/pink' method='get'><button type='submit'>Pink</button></form>";
    html += "<form action='/rainbow' method='get'><button type='submit'>Rainbow</button></form>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleOrange()
{
    set_mode(0);
    handleRoot();
}

void handleGreen()
{
    set_mode(1);
    handleRoot();
}

void handleWhite()
{
    set_mode(2);
    handleRoot();
}

void handlePink()
{
    set_mode(3);
    handleRoot();
}

void handleRainbow()
{
    set_mode(4);
    handleRoot();
}
