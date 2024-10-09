#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <sys/socket.h>
#include <sys/un.h>
#include <csignal>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <atomic>

#include <CommonAPI/CommonAPI.hpp>
#include "@SERVICE_NAME@_server_stubimpl.hpp"

 
using namespace std;

void delay(int delay) {
	std::cout << "[@SERVICE_NAME@] sleep " << delay << "s" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(delay));
}

void delay_ms(int delay) {
	// std::cout << "[@SERVICE_NAME@] sleep " << delay << "ms" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

    std::stringstream ss;
    ss << "[VSimul]["
       << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S")
       << "," << std::setw(6) << std::setfill('0') << ms.count() << "]";
    return ss.str();
}

void log_message(const std::string& message) {
    std::cout << get_current_time() << " " << message << std::endl;
}

// todo
void set@FIELD_NAME@(std::shared_ptr<@SERVICE_NAME@StubImpl> myService, float temperature) {
	int cnt = 1;
    while (true) {
		// vehicle position
		std::cout << "[@SERVICE_NAME@] set_temp_thread: " << temperature << std::endl;
		myService->set@FIELD_NAME@Attribute(temperature);
		temperature += cnt;
		if (cnt == 1) cnt = -1;
		else cnt = 1;
		std::cout << "[@SERVICE_NAME@] set_temp_thread: sleep(1)" << std::endl;
        usleep(1000000); // 1s
    }
}
 
int main() {
	// start SOME/IP
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<@SERVICE_NAME@StubImpl> myService = std::make_shared<@SERVICE_NAME@StubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

	// todo
	// sending thread
	//std::thread th1(set_temperature, myService, 25.0);

    while (true) {
		std::cout << "[@SERVICE_NAME@] main thread .... time interval(1s)" << std::endl;
        delay(1);
    }
 
    return 0;
} 
