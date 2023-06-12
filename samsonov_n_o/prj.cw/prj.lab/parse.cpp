#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <lf_queue/lf_queue.hpp>

namespace parser {

int parse(int argc, char* argv[]) {
    /*std::map<std::string, std::string> arguments;

    for (int i = 1; i < argc; ++i) {
        arguments[argv[i]] = (i + 1 < argc) ? argv[i + 1] : "";
    }
    NTasks = std::stoi(arguments["--ntasks"]);
    BufSize = std::stoi(arguments["--bufsize"]);
    ConsTime = std::stoi(arguments["--ctime"]);
    ProdTime = std::stoi(arguments["--ptime"]);
    
    if (arguments.count("--help") > 0) {
        std::cout << "Опции:" << std::endl;
        std::cout << "--ntasks = " << NTasks << " : количество задач" << std::endl;
        std::cout << "--bufsize = " << BufSize << " : размер буфера очереди" << std::endl;
        std::cout << "--ctime = " << ConsTime << " : время для потребления одной задачи" << std::endl;
        std::cout << "--ntasks = " << ProdTime << " : время для производства одной задачи" << std::endl;
    }
    return 0;*/
}

} // namespace parser