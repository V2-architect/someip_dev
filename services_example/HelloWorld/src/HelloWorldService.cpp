#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "HelloWorldStubImpl.hpp"
 
using namespace std;
 
int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<HelloWorldStubImpl> myService = std::make_shared<HelloWorldStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

	int loc = 10;
    int field_data = 0;
 
    while (true) {
        //std::cout << "[Event] send event data(loc)" << std::endl;
        //myService->fireLocationChangedEvent(loc++);

        //field_data = myService->getXAttribute();
        myService->setXAttribute(0);
        std::cout << "[Field] change the field data: " << field_data << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
 
    return 0;
} 
