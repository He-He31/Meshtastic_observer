#ifndef MESHTASTICCLI_HPP
#define MESHTASTICCLI_HPP

#include "IMeshtastic.hpp"
#include <string>

class MeshtasticCLI : public IMeshtastic {
public:
    // Конструктор принимает идентификатор устройства (например, "/dev/ttyUSB0" или "192.168.1.100")
    // и сразу проверяет его доступность; при неудаче выбрасывает исключение.
    explicit MeshtasticCLI(const std::string& device);

    ~MeshtasticCLI() override = default;

    bool sendMessage(const std::string& destination, const std::string& text) override;
    bool setNetworkMode(NetworkMode mode) override;
    std::vector<NodeInfo> getNodeList() override;

private:
    std::string m_device;                     // идентификатор устройства
    std::string execCommand(const std::string& cmd);   // выполнить системную команду и вернуть stdout
    bool deviceAvailable();                   // проверка доступности устройства
};

#endif