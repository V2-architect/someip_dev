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
#include "Audio_server_stubimpl.hpp"

 
using namespace std;

void delay(int delay) {
	std::cout << "[Audio] sleep " << delay << "s" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(delay));
}

void delay_ms(int delay) {
	// std::cout << "[Audio] sleep " << delay << "ms" << std::endl;
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


int main() {
	// start SOME/IP
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<AudioStubImpl> myService = std::make_shared<AudioStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    while (true) {
		std::cout << "[Audio] main thread .... time interval(1s)" << std::endl;
		std::cout << "[Audio] AudioVolume: " << myService->getAudioVolumeAttribute() << std::endl;
        delay(1);
    }
 
    return 0;
} 
