#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ObjectDetectionProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<ObjectDetectionProxy<>> myProxy = runtime->buildProxy<ObjectDetectionProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "ObjectDetectionClient FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    int retVal;

	/*
	int count1 = 0;
    // [todo] need to work according to the generated API
    myProxy->getObjectTypeEvent().subscribe([&](const int32_t & objtype) {
		count1++;
		if(count1 % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[ObjectDetection][Client] Received ObjectDetection event: " << std::endl;
			std::cout << "[ObjectDetection][Client] objtype: " << objtype << std::endl;
			count1 = 0;
		}
    });
	*/

	int count2 = 0;
    // [todo] need to work according to the generated API
    myProxy->getObjectVelocityAxisEvent().subscribe([&](const float & vel_x, const float & vel_y, const float & vel_z) {
		count2++;
		if(count2 % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[ObjectDetection][Client] Received ObjectDetection event: " << std::endl;
			std::cout << "[ObjectDetection][Client] vel_x: " << vel_x <<
											  ", vel_y: " << vel_y <<
											  ", vel_z: " << vel_z << std::endl;
			count2 = 0;
		}
    });

	int count3 = 0;
    // [todo] need to work according to the generated API
    myProxy->getObjectAccelAxisEvent().subscribe([&](const float & accel_x, const float & accel_y, const float & accel_z) {
		count3++;
		if(count3 % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[ObjectDetection][Client] Received ObjectDetection event: " << std::endl;
			std::cout << "[ObjectDetection][Client] accel_x: " << accel_x <<
											  ", accel_y: " << accel_y <<
											  ", accel_z: " << accel_z << std::endl;
			count3 = 0;
		}
    });

    while(true) {
        std::cout << "[ObjectDetection][Client] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s
    }

    return 0;
}

