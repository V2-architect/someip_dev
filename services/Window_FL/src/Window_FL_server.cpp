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
#include <cstdlib>
#include <ctime>

#include <CommonAPI/CommonAPI.hpp>
#include "Window_FL_server_stubimpl.hpp"

 
using namespace std;

const int32_t WINDOW_POS_MAX = 100;  // closed
const int32_t WINDOW_POS_MIN = 0;
const int32_t WINDOW_CTRL_DELAY_MIN = 60;  // s

const int32_t ARRAY_SIZE = 100;
const int32_t INTERVAL_LEN = 5;

void delay(int delay) {
	std::cout << "[Window_FL] sleep " << delay << "s" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(delay));
}

void delay_ms(int delay) {
	// std::cout << "[Window_FL] sleep " << delay << "ms" << std::endl;
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

void changePosition(std::shared_ptr<Window_FLStubImpl> myService, int32_t interval[INTERVAL_LEN][ARRAY_SIZE], int32_t& curr_pos, int32_t& new_pos) {
	int32_t interval_set = std::rand() % INTERVAL_LEN;
	int32_t interval_idx = 0;

	if (new_pos > curr_pos) {
		while(curr_pos < new_pos) {
			myService->setPositionAttribute(++curr_pos);
			std::this_thread::sleep_for(std::chrono::milliseconds(
				interval[interval_set][interval_idx++]));
			std::cout << "change window position: " << curr_pos << std::endl;
		}
	}

	else if (new_pos < curr_pos) {
		while(curr_pos > new_pos) {
			myService->setPositionAttribute(--curr_pos);
			std::this_thread::sleep_for(std::chrono::milliseconds(
				interval[interval_set][interval_idx++]));
			std::cout << "change window position: " << curr_pos << std::endl;
		}
	}
}

// todo
// position = 0~100
void updatePosition(std::shared_ptr<Window_FLStubImpl> myService) {
	std::srand(static_cast<unsigned int>(std::time(0)));

	// 5sets of series of random values -----S
    int window_ctrl_interval[INTERVAL_LEN][ARRAY_SIZE];
	
    for (int i = 0; i < INTERVAL_LEN; ++i)
		for (int j = 0; j < ARRAY_SIZE; ++j)
			window_ctrl_interval[i][j] = 50 + (std::rand() % 21) - 10;
	// 5sets of series of random values -----E

	int32_t curr_pos = 100;
	int32_t new_pos  = std::rand() % 100;
	int32_t window_control_delay = std::rand() % 61 + WINDOW_CTRL_DELAY_MIN; // per 1~2min (60~120s)


    while (true) {
		// current vehicle window position
		std::cout << "[Window_FL] set_window_position_thread: " << curr_pos << std::endl;
		new_pos = std::rand() % 100;
		window_control_delay = std::rand() % 61 + WINDOW_CTRL_DELAY_MIN; // per 1~2min (60~120s)

		std::cout << "waiting until next window_control: " << window_control_delay << "s" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(window_control_delay));

		changePosition(myService, window_ctrl_interval, curr_pos, new_pos);
		curr_pos = new_pos;
    }
}
 
int main() {
	// start SOME/IP
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<Window_FLStubImpl> myService = std::make_shared<Window_FLStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

	// todo
	// sending thread
	std::thread th1(updatePosition, myService);

    while (true) {
		std::cout << "[Window_FL] main thread .... time interval(1s)" << std::endl;
        delay(1);
    }
 
    return 0;
} 
