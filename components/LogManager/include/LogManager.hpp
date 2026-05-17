#include <string>
#include "SupportFunctions.hpp"

class LogManager{
    std::string log_file_path;
    FILE* file_desc;
    uint8_t LogManagerReady;
    public:
        LogManager(std::string log_file_path);
        ~LogManager();
        int add_log(LogMessage message);
        uint8_t get_log_manger_status();

        


};


