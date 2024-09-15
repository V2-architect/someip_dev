#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/SteeringWheelProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<SteeringWheelProxy<>> myProxy = runtime->buildProxy<SteeringWheelProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "SteeringWheelClient FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    int retVal;

	int count = 0;
    // [todo] need to work according to the generated API
    myProxy->getSteeringWheelStatusEvent().subscribe([&](const float & steerwheel_deg) {
		count++;
		if(count % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[SteeringWheel][Client] Received SteeringWheel event: " << std::endl;
			std::cout << "[SteeringWheel][Client] steerwheel_deg: " << steerwheel_deg << std::endl;
			count = 0;
		}
    });

    while(true) {
        std::cout << "[SteeringWheel][Client] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s
    }

    return 0;
}

