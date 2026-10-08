#ifdef _WIN32
#include "Application.h"

#include "Application.h"

#include "CommandExecutor.h"
#include "SocketServer.h"
#include <windows.h>
#endif 
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <set>



#include <iostream>





void run(Application& app,  int argc, const  char* argv[])
{
    unsigned short port =  argv[1][0] !='\0' ? atoi(argv[1]) : 8089;
    auto   m_server=std::make_unique<SocketServer>();
    if (!m_server->start(port))
    {
        std::cerr << "Cannot start server\n";
        return;
    }

    m_server->run(app );
}
time_t  start , end ;



int mainv1()
{
    Application& app = Application::getInstance();

    app.run();

    return 0;
}
#include <chrono>
#include <thread>
int main(int argc, const char* argv[]) {
 

     
    time(&start);
    mainv1();
 std::this_thread::sleep_for(
        std::chrono::milliseconds(1000)
    );
 

    std::vector<int> vec = {30,20,-20,80,22};
       std::multiset<int>  ms =  {10,1,10,20,23,22,22,33,-98,-98,220};
    std::cout << "10s in Vector: " << std::count(vec.begin(), vec.end(), 10) << std::endl;
    std::cout << "10s in Multiset: " << std::count(ms.begin(), ms.end(), 10) << std::endl;
 
    std::cout << "hello  world" <<std::endl;
    #ifdef _WIN32  
    Sleep(100);   
    #endif 
    time(&end);
    std::cout << "Time taken: " << difftime(end, start) << " seconds" << std::endl;
    Application& app = Application::getInstance();

    app.run();
    app.readFile("data/config.txt");
    std::ifstream file("data/config.txt");
    if (!file.is_open())
    {
        std::cerr << "Cannot open file: data/config.txt" << '\n';
        return 1;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
    run(app, argc, argv);
    file.close();
    return  1 ;
}