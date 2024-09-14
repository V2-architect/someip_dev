#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/@SERVICE_NAME@Proxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<@SERVICE_NAME@Proxy<>> myProxy = runtime->buildProxy<@SERVICE_NAME@Proxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "@SERVICE_NAME@Client FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    int retVal;

    // [todo] need to update according to the generated API
    while(true) {
        // [1] method (out)
		myProxy->@METHOD_NAME@(callStatus, retVal);
		std::cout << "[Method] Got Int Value: '" << retVal << "'\n";
        std::cout << "sleep..." << std::endl;
        usleep(1000000);

        // [2] method (in)
		myProxy->method002(1, callStatus);
		std::cout << "[Method] no return" << "'\n";
        std::cout << "sleep..." << std::endl;
        usleep(1000000);

        // [2] method (in/out)
		myProxy->method003(10, callStatus, retVal);
		std::cout << "[Method] Got Int Value: '" << retVal << "'\n";
        std::cout << "sleep..." << std::endl;
        usleep(1000000);
    }

    return 0;
}

