#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Window_FLProxy.hpp>
#include <cstdlib>
#include <ctime>

using namespace v1::commonapi;


// todo
// global variables
int32_t g_position = 0.0;

int main(int argc, char* argv[]) {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<Window_FLProxy<>> myProxy = runtime->buildProxy<Window_FLProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "[Window_FL][Client] FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    std::cout << "getPosition changedEvent registration!" << std::endl;
    myProxy->getPositionAttribute().getChangedEvent().subscribe([&](const int32_t& value) {
		g_position = value;
        std::cout << "[Window_FL][Client][Main-Thread] Received change Window Position: " << g_position << std::endl;
    });

	// todo
	std::string ecu_name = argv[1];
	if (ecu_name == "ivi") {
		while(true) {
			std::cout << "[Window_FL][Client] while loop... in main thread" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	else {
		std::cout << "[Window_FL][Client] program exit. because IVI only run as Window client." << std::endl;
	}
    return 0;
}

