#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <string>
#include <vector>
#include "NodeInfo.hpp"

class JsonParser {
public:
    static std::string extractString(const std::string& json, const std::string& key);
    static int64_t extractInt(const std::string& json, const std::string& key);
    static double extractDouble(const std::string& json, const std::string& key);
    static bool isValidJson(const std::string& response);
    static std::vector<NodeInfo> parseNodeList(const std::string& output); // теперь принимает полный вывод команды
};

#endif