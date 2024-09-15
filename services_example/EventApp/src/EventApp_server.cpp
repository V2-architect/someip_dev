#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "EventApp_server_stubimpl.hpp"
 
using namespace std;


void delay(int delay) {
	std::cout << "[EventApp] sleep " << delay << "s" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(delay));
}
 
int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<EventAppStubImpl> myService = std::make_shared<EventAppStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    int ev1 = 100;
    int ev2 = 200;
    int ev3 = 300;
    int ev4 = 400;
    int ev5 = 500;
    int ev6 = 600;

    while (true) {
        myService->fireEvent001Event(ev1++);
        delay(1);

        myService->fireEvent002Event(ev2++);
        delay(1);

        myService->fireEvent003Event(ev3++);
        delay(1);
    }
 
    return 0;
} 
