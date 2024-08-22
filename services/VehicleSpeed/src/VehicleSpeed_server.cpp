#include <iostream>
#include <fstream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "VehicleSpeed_server_stubimpl.hpp"
 
using namespace std;


void delay(int delay) {
	std::cout << "[VehicleSpeed] sleep " << delay << "s" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(delay));
}
 
int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<VehicleSpeedStubImpl> myService = std::make_shared<VehicleSpeedStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

	std::ifstream file;


    float vehicle_speed = 0.0;

    while (true) {
		file.open("vehicle_speed.txt");
		if (file >> vehicle_speed) {
            std::cout << "Current speed: " << vehicle_speed << std::endl;
        } else {
            std::cout << "Error reading file" << std::endl;
        }
        file.close();

        myService->fireSpeedEvent(vehicle_speed);
        delay(1);
    }
 
    return 0;
} 
