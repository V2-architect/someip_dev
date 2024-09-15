#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "MethodApp_server_stubimpl.hpp"
 
using namespace std;
 
int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<MethodAppStubImpl> myService = std::make_shared<MethodAppStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    while (true) {
        std::cout << "[MethodApp] sleep 2s" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
 
    return 0;
} 
