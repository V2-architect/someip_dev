#include <iostream>
#include <string>
#include <unistd.h>
#include <random>
#include <cstdlib>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/LoggingProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<LoggingProxy<>> myProxy = runtime->buildProxy<LoggingProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "LoggingClient FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    bool retVal;
	int result;

    std::random_device rd;
    std::mt19937 gen(rd());

    // [todo] need to update according to the generated API
    while(true) {
        // [1] method (out)
		myProxy->get_log_file(callStatus, retVal);
		std::cout << "[Logging] Response: '" << retVal << "'\n";

        result = system("/root/someip_app/pyTFTP/client.py -g ivi.log 10.0.3.5 8467");
        if (result == 0)
            std::cout << "[Logging] received logs from ivi" << std::endl;
        else
            std::cout << "[Logging] failed to receive logs from ivi" << std::endl;
		
		std::uniform_int_distribution<> dis(50, 70);
		int random_sleep = dis(gen);
        std::cout << "sleep...(" << random_sleep << ")" << std::endl;

        sleep(random_sleep);
    }

    return 0;
}

