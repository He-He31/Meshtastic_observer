#include <string>
#include <fstream>
#pragma once
namespace Colors{
    inline std::string red = "\033[31m";
    inline std::string purple = "\033[95m";
    inline std::string cian = "\033[36m";
    inline std::string yellow = "\033[33m";
    inline std::string green = "\033[32m";
    inline std::string end_of_color = "\033[0m";
}


namespace LogMessages{
    inline std::string new_log_entry_header = "========================== New Log Entry ==========================";
    inline std::string end_of_log_entry_header = "========================== Log Entry End ==========================";
    inline std::string error_log_entry = "Error";
    inline std::string send_message_entry  = "Send message";
    inline std::string got_new_data_block_header = "========================== New Data Entry ==========================";
    inline std::string entry_finished = "=================================================================";
    inline std::string found_device = "Found device:";
    inline std::string created_database = "Database initialized:";
    inline std::string meshtastic_found = "Found meshtastic on:";
    inline std::string database_connection_closed = "Database_connection closed";
}


typedef struct MessageDescription {
    std::string message_type;
    std::string message_color;
    std::string message;
}LogMessage;