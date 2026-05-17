#ifndef NODEINFO_HPP
#define NODEINFO_HPP

#include <string>
#include <cstdint>

struct NodeInfo {
    std::string id;          // ID устройства (например, "!ab12cd34")
    int32_t rssi = 0;        // уровень сигнала в dBm
    double snr = 0.0;        // отношение сигнал/шум
    uint32_t hopCount = 0;   // количество узлов до приёмника
};

#endif