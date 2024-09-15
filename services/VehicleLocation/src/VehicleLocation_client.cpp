#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/VehicleLocationProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<VehicleLocationProxy<>> myProxy = runtime->buildProxy<VehicleLocationProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "VehicleLocationClient FAIL: Returned  proxy is NULL! - Giving up!\n";
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
    myProxy->getLocationInfoEvent().subscribe([&](const float & lati, const float & longi, const float & alti) {
		count++;
		if(count % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[VehicleLocation][Client] Received VehicleLocation event: " << std::endl;
			std::cout << "[VehicleLocation][Client] lati: " << lati <<
											  ", longi: " << longi <<
											  ", alti: " << alti << std::endl;
			count = 0;
		}
    });

    while(true) {
        std::cout << "[VehicleLocation][Client] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s
    }

    return 0;
}

