#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/VehicleAccelProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<VehicleAccelProxy<>> myProxy = runtime->buildProxy<VehicleAccelProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "VehicleAccelClient FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    int retVal;

    // [todo] need to work according to the generated API
    myProxy->getAccelAxisEvent().subscribe([&](const float & accel_x, const float & accel_y, const float & accel_z) {
        std::cout << "[VehicleAccel][Client] Received VehicleAccel event: " << accel_x << std::endl;
        std::cout << "[VehicleAccel][Client] accel_x: " << accel_x <<
                                          ", accel_y: " << accel_y <<
                                          ", accel_z: " << accel_z << std::endl;
    });

    while(true) {
        std::cout << "[VehicleAccel][Client] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s
    }

    return 0;
}

