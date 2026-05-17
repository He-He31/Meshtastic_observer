#include "SQLiteManager.hpp"

int main(){


table_conf_t test_table ={
    .table_name = "TEST_TABLE2",
    .table_conf_list= {"ID INTEGER PRIMARY KEY", "T1 XT", "F2 INTEGER"}
};

SQLiteManager m1 = SQLiteManager("/home/xv12rq/LeetCode_tasks/TRPO_Lab/build/database.db");
//m1.create_table(test_table);
std::vector<std::string> data = {"46","'Test1'","34"};
m1.add_new_line(data,test_table);


}