#include <string>
class ProcessHandler{


    static inline std::string db_path;

    public:
        ProcessHandler(ProcessHandler const &) = delete;
        ProcessHandler &operator=(ProcessHandler const &) = delete;

        static ProcessHandler& getDBhandler(){
            static ProcessHandler DB_handler;
            return DB_handler;
        };

    private:
        ProcessHandler() = default;
    
};