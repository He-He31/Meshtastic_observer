#ifndef IMESHTASTIC_HPP
#define IMESHTASTIC_HPP

#include <string>
#include <vector>
#include "NetworkMode.hpp"
#include "NodeInfo.hpp"

class IMeshtastic {
public:
    virtual ~IMeshtastic() = default;

    // Проверка наличия устройства (реализована в конструкторе конкретного класса)
    // Сам конструктор – часть реализации, в интерфейсе не описывается.

    virtual bool sendMessage(const std::string& destination, const std::string& text) = 0;
    virtual bool setNetworkMode(NetworkMode mode) = 0;
    virtual std::vector<NodeInfo> getNodeList() = 0;
};

#endif