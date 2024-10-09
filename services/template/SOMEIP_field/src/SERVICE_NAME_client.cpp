#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/@SERVICE_NAME@Proxy.hpp>

using namespace v1::commonapi;


void recv_field_cb(const CommonAPI::CallStatus& callStatus, const float& val) {
    std::cout << "[field][Async] Receive callback: " << val << std::endl;
}

void handle_field_async(std::shared_ptr<HelloWorldProxy<>> myProxy, float value) {
    CommonAPI::CallStatus callStatus;

    // [field] Setter Asynchronous call to set attribute of service
    CommonAPI::CallInfo info(1000);
    info.sender_ = 5678;
    std::function<void(const CommonAPI::CallStatus&, int32_t)> fcb = recv_field_cb;
    myProxy->getXAttribute().setValueAsync(value, fcb, &info);
}

void handle_field_sync(std::shared_ptr<HelloWorldProxy<>> myProxy, float value) {
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

	int count = 0;
    // [todo] need to work according to the generated API
    myProxy->get@EVENT_NAME@Event().subscribe([&](const float & event1, const float & event2, const float & event3) {
		count++;
		if(count % 50 == 0) { // 20ms x 50 = 1s
			std::cout << "[@SERVICE_NAME@][Client] Received @SERVICE_NAME@ event: " << std::endl;
			std::cout << "[@SERVICE_NAME@][Client] accel_x: " << accel_x <<
											  ", accel_y: " << accel_y <<
											  ", accel_z: " << accel_z << std::endl;
			count = 0;
		}
    });

    float field_value = 0;
    while(true) {
        std::cout << "[@SERVICE_NAME@][Client] while loop... in main thread" << std::endl;
        usleep(1000000); // 1s

		handle_field_sync(myProxy, field_value++);
		handle_field_async(myProxy, field_value+100);
    }

    return 0;
}

