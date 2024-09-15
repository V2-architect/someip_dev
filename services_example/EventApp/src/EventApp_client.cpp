#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/EventAppProxy.hpp>

using namespace v1::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<EventAppProxy<>> myProxy = runtime->buildProxy<EventAppProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "EventAppClient FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    int retVal;

    myProxy->getEvent001Event().subscribe([&](const int32_t& event) {
        std::cout << "[Event-normal] Received Event001 event: " << event << std::endl;
    });

    myProxy->getEvent002Event().subscribe([&](const int32_t& event) {
        std::cout << "[Event-normal] Received Event002 event: " << event << std::endl;
    });

    myProxy->getEvent003Event().subscribe([&](const int32_t& event) {
        std::cout << "[Event-normal] Received Event003 event: " << event << std::endl;
    });

    myProxy->getEvent004SelectiveEvent().subscribe([&](const int32_t& event) {
        std::cout << "[Event-selective] Received Event004 event: " << event << std::endl;
    });

    myProxy->getEvent005SelectiveEvent().subscribe([&](const int32_t& event) {
        std::cout << "[Event-selective] Received Event005 event: " << event << std::endl;
    });

    myProxy->getEvent006SelectiveEvent().subscribe([&](const int32_t& event) {
        std::cout << "[Event-selective] Received Event006 event: " << event << std::endl;
    });

    while(true) {
        std::cout << "[EventAppClient] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s
    }

    return 0;
}

