#ifndef NETWORKMODE_HPP
#define NETWORKMODE_HPP

enum class NetworkMode {
    Radio,   // работа через радио (CLIENT/ROUTER/REPEATER)
    WiFi,    // использование WiFi как транспорта
    GPS      // режим трекера (TRACKER)
};

#endif