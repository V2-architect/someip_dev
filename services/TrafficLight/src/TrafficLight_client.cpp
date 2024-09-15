#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/TrafficLightProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<TrafficLightProxy<>> myProxy = runtime->buildProxy<TrafficLightProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "TrafficLightClient FAIL: Returned  proxy is NULL! - Giving up!\n";
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
    myProxy->getTrafficLightStatusEvent().subscribe([&](const int32_t & trafficlight_type, const int32_t & trafficlight_status) {
		count++;
		if(count % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[TrafficLight][Client] Received TrafficLight event: " << std::endl;
			std::cout << "[TrafficLight][Client] trafficlight_type: " << trafficlight_type <<
											  ", trafficlight_status: " << trafficlight_status << std::endl;
			count = 0;
		}
    });

    while(true) {
        std::cout << "[TrafficLight][Client] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s
    }

    return 0;
}

