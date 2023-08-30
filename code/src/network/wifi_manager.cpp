
#include <WiFi.h>

#include "wifi_manager.h"
#include "..\display\animations.h"


/***
 * TODO: wifi manager
 */


void WiFiManager::exec() {
    this->update();
}


void WiFiManager::update() {
    if (WiFi.isConnected()) return;
    else this->connectWiFi("", "");
}


void WiFiManager::connectWiFi(char *ssid, char *password) {
    Serial.print("WiFi: connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    Serial.print("WiFi: connected to ");
    Serial.println(ssid);

    Animations::wifiConnected();
}


void WiFiManager::disconnectWiFi() {
    WiFi.disconnect();
    Animations::wifiDisconnected();
}


void WiFiManager::checkBest() {
    connectWiFi();
}


WiFiManager wifi_manager;