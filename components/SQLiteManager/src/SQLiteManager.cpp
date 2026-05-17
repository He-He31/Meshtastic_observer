#include "SQLiteManager.hpp"
#include "db_types.h"
#include "sqlite3.h"
#include <string>
#include <regex>

void SQLiteManager::add_new_line(std::vector<std::string> data,table_conf_t table_conf){

    std::string buffer = "INSERT INTO " + table_conf.table_name + " VALUES (";

   for(auto iter = data.begin(); iter!= data.end(); iter++){
        buffer = buffer+*iter;
        if(iter+1 == data.end()){
            buffer = buffer+")";
        }
        else{
            buffer = buffer+", ";
        }
    }

    char* messaggeError;
    int exit = sqlite3_exec(db, buffer.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
       fprintf(stderr, "Error creating table: %s\n", sqlite3_errmsg(db));
        sqlite3_free(messaggeError);
    }
    

};


SQLiteManager::~SQLiteManager(){
    //sqlite3_finalize(res);
    sqlite3_close(db);


};


void SQLiteManager::create_table(table_conf_t table_conf){
    std::string buffer = "CREATE TABLE IF NOT EXISTS ";
    buffer = buffer+table_conf.table_name;
    buffer = buffer+" (";

    
    for(auto iter = table_conf.table_conf_list.begin(); iter!= table_conf.table_conf_list.end(); iter++){
        buffer = buffer+*iter;
        if(iter+1 == table_conf.table_conf_list.end()){
            buffer = buffer+")";
        }
        else{
            buffer = buffer+", ";
        }
    }
    
    char* messaggeError;
    int exit = sqlite3_exec(db, buffer.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
       fprintf(stderr, "Error creating table: %s\n", sqlite3_errmsg(db));
        sqlite3_free(messaggeError);
    }
};






void SQLiteManager::delete_table(table_conf_t table_conf){
    std::string buffer = "DROP TABLE IF EXISTS";
    buffer = buffer+" ";
    buffer = buffer+table_conf.table_name;
    char* messaggeError;
    int exit = sqlite3_exec(db, buffer.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
       fprintf(stderr, "Error deleting table: %s\n", sqlite3_errmsg(db));
        sqlite3_free(messaggeError);
    }
};



SQLiteManager::SQLiteManager(std::string db_location): db{NULL}, last_operation_code{0}{

    int rc = sqlite3_open(db_location.c_str(), &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        last_operation_code = 1;
    }
    else{
        fprintf(stdout, "Open databse: successfull\n");
        last_operation_code = 0; 
    }
};

