
#pragma once
#include <string>
#include <vector>
#include <variant>

typedef struct{
    std::string table_name;
    std::vector<std::string> table_conf_list;
}table_conf_t;


typedef struct{
    std::string table_name;
    std::vector<std::string> string_parameters;
    std::vector<int> integer_parameners;
    std::vector<double> double_parameters;
}table_data_insert;


enum data_types {
    INT_TYPE,
    STRING_TYPE,
    DOUBLE_TYPE

};

