#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/HelloWorldProxy.hpp>

using namespace v1::commonapi;

void recv_method_cb(const CommonAPI::CallStatus& callStatus, const std::string& returnMessage) {
    std::cout << "[Method][Async] Result of asynchronous call of foo: " << std::endl;
    std::cout << "   callStatus: " << ((callStatus == CommonAPI::CallStatus::SUCCESS) ? "SUCCESS" : "NO_SUCCESS")
                    << std::endl;
    std::cout << "   Got message: '" << returnMessage << "'\n";
}


void recv_field_cb(const CommonAPI::CallStatus& callStatus, const int32_t& val) {
    std::cout << "[field][Async] Receive callback: " << val << std::endl;
}

void handle_field_async(std::shared_ptr<HelloWorldProxy<>> myProxy, int32_t value) {
    CommonAPI::CallStatus callStatus;

    // [field] Setter Asynchronous call to set attribute of service
    CommonAPI::CallInfo info(1000);
    info.sender_ = 5678;
    std::function<void(const CommonAPI::CallStatus&, int32_t)> fcb = recv_field_cb;
    myProxy->getXAttribute().setValueAsync(value, fcb, &info);
}


void handle_field_sync(std::shared_ptr<HelloWorldProxy<>> myProxy, int32_t value) {
    CommonAPI::CallStatus callStatus;

	int32_t value_from_server;
	// [field] Setter
	myProxy->getXAttribute().setValue(
		value, callStatus, value_from_server);
	std::cout << "[Field] Set attribute -> " << value << std::endl;
	std::cout << "[Field] --> the value from server -> " << value_from_server << std::endl;

}


int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<HelloWorldProxy<>> myProxy = runtime->buildProxy<HelloWorldProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "HelloWorldClient FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    std::cout << "[Method] sayHello Async requested!" << std::endl;
	std::function<void(const CommonAPI::CallStatus&, const std::string&)> fcb = recv_method_cb;
	myProxy->sayHelloAsync("Bob_async", fcb);

    std::cout << "[Method] sayHello Sync requested!" << std::endl;
    myProxy->sayHello("Bob", callStatus, returnMessage);
    std::cout << "[Method] Got message: '" << returnMessage << "'\n";

    std::cout << "[Method] sayHello Async requested!" << std::endl;
	myProxy->sayHelloAsync("Bob_async", fcb);

    std::cout << "[Method][FireAndForget] sayHelloFnF Sync requested!" << std::endl;
	myProxy->sayHelloFnF("Bob_FnF_Ssync", callStatus);


    int32_t field_value = 0;
    int32_t field_value_from_server = 0;

	// [field] Getter
    myProxy->getXAttribute().getValue(callStatus, field_value);
    std::cout << "[Field] Get Attribute value: " << field_value << std::endl;




	// [field] Notifier
    myProxy->getXAttribute().getChangedEvent().subscribe([&](const int32_t& val) {
        std::cout << "[Field] Received change msg: " << val << std::endl;
        field_value = val;
    });

	// LocationChanged Event (event)
	/*
    myProxy->getLocationChangedEvent().subscribe([&](const int32_t& val) {
		std::cout << "[Event] Received LocationChanged event: " << val << std::endl;
    });
	*/

    
    while(true) {
        std::cout << "sleep..." << std::endl;
        usleep(1000000);

		// field communication
		handle_field_sync(myProxy, field_value++);
		handle_field_async(myProxy, field_value+100);
    }


    return 0;
}

