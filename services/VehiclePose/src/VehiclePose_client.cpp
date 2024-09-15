#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/VehiclePoseProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<VehiclePoseProxy<>> myProxy = runtime->buildProxy<VehiclePoseProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "VehiclePoseClient FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    int retVal;

	int count1 = 0;
	int count2 = 0;
    // [todo] need to work according to the generated API
    myProxy->getVehiclePositionEvent().subscribe([&](const float & vehicle_roll, const float & vehicle_pitch, const float & vehicle_heading) {
		count1++;
		if (count1 % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[VehiclePose][Client] vehicle_roll: " << vehicle_roll <<
											 ", vehicle_pitch: " << vehicle_pitch <<
											 ", vehicle_heading: " << vehicle_heading << std::endl;
			count1 = 0;
		}
    });

    myProxy->getAngularVelocityEvent().subscribe([&](const float & angular_velocity_x, const float & angular_velocity_y, const float & angular_velocity_z) {
		count2++;
		if (count2 % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[VehiclePose][Client] angular_velocity_x: " << angular_velocity_x <<
											 ", angular_velocity_y: " << angular_velocity_y <<
											 ", angular_velocity_z: " << angular_velocity_z << std::endl;
			count2 = 0;
		}
    });



    while(true) {
        std::cout << "[VehiclePose][Client] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s
    }

    return 0;
}

