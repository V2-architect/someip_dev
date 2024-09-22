#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <sys/socket.h>
#include <sys/un.h>
#include <csignal>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <atomic>

#include <CommonAPI/CommonAPI.hpp>
#include "Logging_server_stubimpl.hpp"

 
using namespace std;

int main() {
	// start SOME/IP
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<LoggingStubImpl> myService = std::make_shared<LoggingStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    while (true) {
        std::cout << "[Logging] sleep 2s" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
} 
