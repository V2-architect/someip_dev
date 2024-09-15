#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/DrivingProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<DrivingProxy<>> myProxy = runtime->buildProxy<DrivingProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "DrivingClient FAIL: Returned  proxy is NULL! - Giving up!\n";
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
    // [todo] need to work according to the generated API
    myProxy->getAccelStatusEvent().subscribe([&](const float & accel) {
		count1++;
		if(count1 % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[Driving][Client] Received Driving event: " << std::endl;
			std::cout << "[Driving][Client] accel: " << accel << std::endl;
			count1 = 0;
		}
    });


	int count2 = 0;
    myProxy->getBrakeStatusEvent().subscribe([&](const float & brake) {
		count2++;
		if(count2 % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[Driving][Client] Received Driving event: " << std::endl;
			std::cout << "[Driving][Client] brake: " << brake << std::endl;
			count2 = 0;
		}
    });

    while(true) {
        std::cout << "[Driving][Client] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s
    }

    return 0;
}

