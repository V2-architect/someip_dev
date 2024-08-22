#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/VehicleSpeedProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<VehicleSpeedProxy<>> myProxy = runtime->buildProxy<VehicleSpeedProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "VehicleSpeedClient FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    int retVal;

    myProxy->getSpeedEvent().subscribe([&](const float & event) {
        std::cout << "[Event-normal] Received VehicleSpeed event: " << event << std::endl;
    });

    while(true) {
        std::cout << "[VehicleSpeedClient] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s
    }

    return 0;
}

