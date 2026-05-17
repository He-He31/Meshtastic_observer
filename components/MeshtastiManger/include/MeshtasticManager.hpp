#include <string>
#include <vector>
class Meshatstic_node {

    static inline std::string port_name;
    public:
        Meshatstic_node(Meshatstic_node const&) = delete;
        Meshatstic_node& operator=(Meshatstic_node const&) = delete;

        static Meshatstic_node& getMeshtasticHandler(){
            static Meshatstic_node Meshtastic_handler;
            return Meshtastic_handler;
        };
        
        static void initialize(const std::string& port) {
            port_name = port;
        }

    private:
        Meshatstic_node() = default;

    public: 
        std::vector<std::string> scan_ble_device();
        



};


//необходимости распареливать процессы нет. Все программные сущности д.б. singletone
//Основной интерфейс программы надо сделать через Facade
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