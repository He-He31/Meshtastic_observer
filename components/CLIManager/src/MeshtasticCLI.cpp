#include "MeshtasticCLI.hpp"
#include "JsonParser.hpp"
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <iostream>
MeshtasticCLI::MeshtasticCLI(const std::string& device) : m_device(device) {
    if (!deviceAvailable()) {
        throw std::runtime_error("Устройство " + device + " не найдено или не отвечает");
    }
}

std::string MeshtasticCLI::execCommand(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Ошибка выполнения команды: " + cmd);
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

bool MeshtasticCLI::deviceAvailable() {
    // Используем команду "meshtastic --info" для проверки
    std::string cmd = "meshtastic --port " + m_device + " --info 2>/dev/null";
    std::string response = execCommand(cmd);
    return JsonParser::isValidJson(response);
}

bool MeshtasticCLI::sendMessage(const std::string& destination, const std::string& text) {
    // Экранирование текста для shell не показано для краткости
    std::string cmd = "meshtastic --port " + m_device + " --sendtext \"" + text + "\" 2>&1";
    std::cout << cmd << std::endl;
    std::string response = execCommand(cmd);
    return response.find("Error") == std::string::npos;
}

bool MeshtasticCLI::setNetworkMode(NetworkMode mode) {
    std::string role;
    switch (mode) {
        case NetworkMode::Radio:
            role = "CLIENT";   // или ROUTER, REPEATER – зависит от желаемой логики
            break;
        case NetworkMode::WiFi:
            role = "WIFI_CLIENT"; // предположительный режим
            break;
        case NetworkMode::GPS:
            role = "TRACKER";
            break;
        default:
            return false;
    }
    std::string cmd = "meshtastic --port " + m_device + " --set role " + role;
    std::string response = execCommand(cmd + " 2>&1");
    return response.find("Error") == std::string::npos;
}

std::vector<NodeInfo> MeshtasticCLI::getNodeList() {
    std::string cmd = "meshtastic --port " + m_device + " --nodes --info";
    std::string response = execCommand(cmd);
    if (!JsonParser::isValidJson(response)) {
        return {};
    }
    std::cout<<response;
    std::vector <NodeInfo> v1 =  JsonParser::parseNodeList(response);
    for (auto iter =v1.begin(); iter!=v1.end();iter++){
        std::cout << iter->id<<std::endl;
        std::cout << iter->rssi << std::endl;
    }
    return JsonParser::parseNodeList(response);
}