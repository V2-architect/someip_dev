#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/@SERVICE_NAME@Proxy.hpp>

using namespace v1::commonapi;


// todo
// global variables
float g_temp = 0.0;

void recv_field_cb(const CommonAPI::CallStatus& callStatus, const float& val) {
    std::cout << "[@SERVICE_NAME@][Client][Field-Async] Receive callback: " << val << std::endl;
}

void handle_field_async(std::shared_ptr<@SERVICE_NAME@Proxy<>> myProxy, float value) {
    CommonAPI::CallStatus callStatus;

    // [@SERVICE_NAME@] Setter Asynchronous call to set attribute of service
    CommonAPI::CallInfo info(1000);
    info.sender_ = 5678;
    std::function<void(const CommonAPI::CallStatus&, int32_t)> fcb = recv_field_cb;
    myProxy->get@FIELD_NAME@Attribute().setValueAsync(value, fcb, &info);
}

void handle_field_sync(std::shared_ptr<@SERVICE_NAME@Proxy<>> myProxy, float value) {
    CommonAPI::CallStatus callStatus;

	CommonAPI::CallInfo info(1000);
    info.sender_ = 5678;
	//float &value_from_server = value;
	// [@SERVICE_NAME@] Setter
	//myProxy->get@FIELD_NAME@Attribute().setValue(
	//	value, callStatus, &value_from_server);

	std::cout << "[@SERVICE_NAME@][Client][Thread] Set attribute -> " << value << std::endl;
	myProxy->get@FIELD_NAME@Attribute().setValue(
		value, callStatus, value, &info);
	std::cout << "[@SERVICE_NAME@][Client][Thread] Set attribute reponse -> " << value << std::endl;
}

int main(int argc, char* argv[]) {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<@SERVICE_NAME@Proxy<>> myProxy = runtime->buildProxy<@SERVICE_NAME@Proxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "[@SERVICE_NAME@][Client] FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    std::cout << "get@FIELD_NAME@ changedEvent registration!" << std::endl;
    myProxy->get@FIELD_NAME@Attribute().getChangedEvent().subscribe([&](const float& value) {
		g_temp = value;
        std::cout << "[@SERVICE_NAME@][Client][Main-Thread] Received change @FIELD_NAME@: " << g_temp << std::endl;
    });

	// todo
	std::string ecu_name = argv[1];
	if (ecu_name == "ivi") {
		while(true) {
			std::cout << "[@SERVICE_NAME@][Client] while loop... in main thread" << std::endl;
			usleep(1000000); // 1s
			handle_field_sync(myProxy, g_temp++);
			//handle_field_async(myProxy, temperature+100);
		}
	}
	if (ecu_name == "cluster") {
		while(true) {
			std::cout << "[@SERVICE_NAME@][Client][Only Listen] while loop... in main thread" << std::endl;
			usleep(1000000); // 1s
		}
	}
    return 0;
}

