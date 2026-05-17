#include "JsonParser.hpp"
#include <algorithm>
#include <sstream>
#include <cctype>
#include <stdexcept>

std::string JsonParser::extractString(const std::string& json, const std::string& key) {
    std::string search = "\"" + key + "\":";
    size_t pos = json.find(search);
    if (pos == std::string::npos) return "";

    pos += search.length();
    // пропускаем пробелы и открывающую кавычку
    while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t')) ++pos;
    if (pos < json.size() && json[pos] == '"') {
        ++pos;
        size_t end = json.find('"', pos);
        if (end == std::string::npos) return "";
        return json.substr(pos, end - pos);
    } else {
        // значение без кавычек (число, true/false/null)
        size_t end = pos;
        while (end < json.size() && (std::isalnum(json[end]) || json[end] == '.' || json[end] == '-')) ++end;
        return json.substr(pos, end - pos);
    }
}

int64_t JsonParser::extractInt(const std::string& json, const std::string& key) {
    std::string s = extractString(json, key);
    if (s.empty()) return 0;
    return std::stoll(s);
}

double JsonParser::extractDouble(const std::string& json, const std::string& key) {
    std::string s = extractString(json, key);
    if (s.empty()) return 0.0;
    return std::stod(s);
}

bool JsonParser::isValidJson(const std::string& response) {
    return !response.empty() && response.find('{') != std::string::npos;
}

std::vector<NodeInfo> JsonParser::parseNodeList(const std::string& output) {
    std::vector<NodeInfo> nodes;

    // 1. Найти начало секции "Nodes in mesh:"
    std::string marker = "Nodes in mesh:";
    size_t sectionPos = output.find(marker);
    if (sectionPos == std::string::npos) {
        // Иногда может быть "Nodes in mesh:" без пробела? Оставим как есть.
        return nodes;
    }

    // 2. Найти открывающую фигурную скобку после маркера
    size_t openBrace = output.find('{', sectionPos + marker.length());
    if (openBrace == std::string::npos) return nodes;

    // 3. Найти соответствующую закрывающую скобку, учитывая вложенность
    int braceDepth = 0;
    size_t closeBrace = std::string::npos;
    for (size_t i = openBrace; i < output.size(); ++i) {
        if (output[i] == '{') braceDepth++;
        else if (output[i] == '}') {
            braceDepth--;
            if (braceDepth == 0) {
                closeBrace = i;
                break;
            }
        }
    }
    if (closeBrace == std::string::npos) return nodes;

    // 4. Вырезаем содержимое между { и } (сам объект узлов)
    std::string meshObj = output.substr(openBrace + 1, closeBrace - openBrace - 1);

    // 5. Ищем все ключи вида "!bba89a40": { ... }
    size_t pos = 0;
    while (pos < meshObj.size()) {
        // ищем начало ключа (кавычка)
        size_t keyStart = meshObj.find('"', pos);
        if (keyStart == std::string::npos) break;
        size_t keyEnd = meshObj.find('"', keyStart + 1);
        if (keyEnd == std::string::npos) break;
        std::string nodeId = meshObj.substr(keyStart + 1, keyEnd - keyStart - 1);
        // ищем двоеточие
        size_t colon = meshObj.find(':', keyEnd + 1);
        if (colon == std::string::npos) break;
        // ищем открывающую { для объекта узла
        size_t nodeObjStart = meshObj.find('{', colon + 1);
        if (nodeObjStart == std::string::npos) break;

        // ищем соответствующую закрывающую } для этого объекта
        int depth = 0;
        size_t nodeObjEnd = std::string::npos;
        for (size_t i = nodeObjStart; i < meshObj.size(); ++i) {
            if (meshObj[i] == '{') depth++;
            else if (meshObj[i] == '}') {
                depth--;
                if (depth == 0) {
                    nodeObjEnd = i;
                    break;
                }
            }
        }
        if (nodeObjEnd == std::string::npos) break;

        std::string nodeJson = meshObj.substr(nodeObjStart, nodeObjEnd - nodeObjStart + 1);

        // 6. Извлекаем нужные поля
        NodeInfo node;
        node.id = nodeId;
        node.rssi = static_cast<int32_t>(extractInt(nodeJson, "rssi")); // 0 если нет
        // SNR может быть с плавающей точкой или целым
        node.snr = extractDouble(nodeJson, "snr");
        // hopCount – ищем hopsAway
        node.hopCount = static_cast<uint32_t>(extractInt(nodeJson, "hopsAway"));

        nodes.push_back(node);

        pos = nodeObjEnd + 1;
    }

    return nodes;
}