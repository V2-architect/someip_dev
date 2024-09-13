#include <iostream>
#include <fstream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "VehicleGear_server_stubimpl.hpp"
 
using namespace std;


void delay(int delay) {
	std::cout << "[VehicleGear] sleep " << delay << "s" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(delay));
}
 
int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<VehicleGearStubImpl> myService = std::make_shared<VehicleGearStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

	std::ifstream file;


    int vehicle_gear = 0;

    while (true) {
		file.open("vehicle_gear.txt");
		if (file >> vehicle_gear) {
            std::cout << "Current gear: " << vehicle_gear << std::endl;
        } else {
            std::cout << "Error reading file" << std::endl;
        }
        file.close();

        myService->fireGearEvent(vehicle_gear);
        delay(1);
    }
 
    return 0;
} 
