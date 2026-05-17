#include <string>
#include <vector>
#include "db_types.h"

#include "sqlite3.h"



class SQLiteManager{
    sqlite3 *db;
    size_t last_operation_code;
    std::vector<table_conf_t> db_content;


    public:
        SQLiteManager(std::string db_location);
        ~SQLiteManager();
        void create_table(table_conf_t table_conf);
        void delete_table(table_conf_t table_conf);
        void add_new_line(std::vector<std::string> data,table_conf_t table_conf);

}; 



