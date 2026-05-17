#include "LogManager.hpp"
#include "SupportFunctions.hpp"
#include <iostream>
LogManager::LogManager(std::string log_file_path) : LogManagerReady(0){
    file_desc = fopen(log_file_path.c_str(),"a+");
    if(!file_desc){
        LogManagerReady = 0;
        throw "Error while openning log file";
    }
    else{
        LogManagerReady = 1;
    }
}

LogManager::~LogManager(){
    std::string buff = Colors::yellow + LogMessages::end_of_log_entry_header + Colors::end_of_color + "\n";
    //const char* buffer = buff.c_str();
    if(LogManagerReady){
        fwrite(buff.c_str(),buff.size(),1,file_desc);
        fclose(file_desc);
    }


}
int LogManager::add_log(LogMessage message){



    
    if(LogManagerReady){

        std::string log_message = message.message_color + message.message_type + message.message + Colors::end_of_color + "\n";
        size_t elments_write = fwrite(log_message.c_str(),log_message.size(),1,file_desc);
        return elments_write;
    }
    else{
        return -1;
    }

}


uint8_t LogManager::get_log_manger_status(){
    return LogManagerReady;
}