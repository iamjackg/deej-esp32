#include <WiFi.h>
#include <WiFiUdp.h>

#include "configuration.h"

#define NUM_SLIDERS 5

WiFiUDP Udp;
IPAddress destIp;

byte pins[6] = {36, 39, 34, 35, 32, 33};

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    destIp = IPAddress();
    destIp.fromString(DEST_IP);

    Serial.begin(115200);
    Serial.println();
    Serial.println("Configuring access point...");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true);
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(HOSTNAME);
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    analogReadResolution(10);
}

void loop() {
    uint i;
    uint readings[5];
    for (i = 0; i < NUM_SLIDERS; i++) {
        readings[i] = analogRead(pins[i]);
    }
    String builtString = String("");

    for (int i = 0; i < NUM_SLIDERS; i++) {
        builtString += String((int)readings[i]);

        if (i < NUM_SLIDERS - 1) {
            builtString += String("|");
        }
    }
    Serial.println(builtString + "\n");

    Udp.beginPacket(destIp, 16990);
    Udp.write((uint8_t *) builtString.c_str(), builtString.length());
    Udp.endPacket();
    delay(10);
}