
#pragma once

#ifndef CODE_WIFI_MANAGER_H
#define CODE_WIFI_MANAGER_H

#include <vector>
#include <TaskManagerIO.h>

struct WiFi_information {
    char *ssid;
    char *password;
};

class WiFiManager: public Executable {
public:
    void exec() override;

    void connectWiFi(char *ssid, char* password);
    void update();
    void appand();
private:
    std::vector<struct WiFi_information> access_points;

    void connectWiFi();
    void disconnectWiFi();
    void checkBest();
};

#endif