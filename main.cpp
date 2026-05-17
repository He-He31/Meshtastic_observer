#include <iostream>
#include <stdexcept>
#include "MeshtasticCLI.hpp"

int main() {
    try {
        // Создаём объект компонента, передавая идентификатор устройства.
        // Конструктор сразу проверяет доступность устройства.
        // Если устройство не отвечает, выбрасывается исключение std::runtime_error.
        IMeshtastic* mesh = new MeshtasticCLI("/dev/ttyACM0");  // или "192.168.1.100" для TCP

        // 1. Отправка сообщения
        bool ok = mesh->sendMessage("!ab12cd34", "Hello from C++ component");
        std::cout << "Send message: " << (ok ? "success" : "failed") << std::endl;

        // // 2. Переключение режима сети (например, включить GPS-трекер)
        // ok = mesh->setNetworkMode(NetworkMode::GPS);
        // std::cout << "Set mode GPS: " << (ok ? "success" : "failed") << std::endl;

        // 3. Получение списка узлов
        std::vector<NodeInfo> nodes = mesh->getNodeList();
        std::cout << "Nodes count: " << nodes.size() << std::endl;
        for (const auto& node : nodes) {
            std::cout << "ID: " << node.id
                      << ", RSSI: " << node.rssi << " dBm"
                      << ", SNR: " << node.snr
                      << ", Hops: " << node.hopCount << std::endl;
        }

        delete mesh;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}