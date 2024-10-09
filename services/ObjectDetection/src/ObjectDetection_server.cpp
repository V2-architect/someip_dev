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
#include "ObjectDetection_server_stubimpl.hpp"

 
using namespace std;

void delay(int delay) {
	std::cout << "[ObjectDetection] sleep " << delay << "s" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(delay));
}

void delay_ms(int delay) {
	// std::cout << "[ObjectDetection] sleep " << delay << "ms" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

// [todo]
// [example]: const char* socket_path = "/root/someip_app/tmp/uds_vehicle_speed";
const char* socket_path = "/tmp/uds/uds_objectdetection";
int server_socket = -1;
std::atomic<bool> running(true);

// [todo] need to update according to the generated API
// [todo] shared data(global variable) between socket thread and main thread
//float vehicle_speed_data[3] = {0.0, 0.0, 0.0};
// receive buffer
char buffer[sizeof(int) + sizeof(float)*6];

// shared datas (3categories)
int32_t objtype = 0;
float obj_vel_axis[3] = {0.0, 0.0, 0.0};
float obj_accel_axis[3] = {0.0, 0.0, 0.0};
float obj_info[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
int32_t ObjectType_interval = 0;
int32_t ObjectVelocityAxis_interval = 0;
int32_t ObjectAccelAxis_interval = 0;


void cleanup_and_exit(int signum) {
    running = false;
    if (server_socket != -1) {
        close(server_socket);
    }
    unlink(socket_path);
    std::cout << "Server shutting down gracefully" << std::endl;
    exit(0);
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

void socket_thread() {
    // remove existing socket file
    unlink(socket_path);

    // create socket
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket < 0) {
        log_message("Failed to create socket");
        return;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

    if (bind(server_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        log_message("Failed to bind socket");
        close(server_socket);
        return;
    }

    if (listen(server_socket, 1) < 0) {
        log_message("Failed to listen on socket");
        close(server_socket);
        return;
    }

    log_message("Server is listening");

	int count = 0;
    while (running) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket < 0) {
            if (running) {
                log_message("Failed to accept client connection");
            }
            continue;
        }

        log_message("Client connected");

        while (running) {
			count++;
            // [todo] need to update according to the generated API ----------- START
            //ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
            ssize_t bytes_received = recv(client_socket, obj_info, sizeof(obj_info), 0);
            if (bytes_received <= 0) {
                break;
            }

			// [todo] update vehicle data array
			if (count % 50 == 0) {
				// unpacking
				/*
				memcpy(&objtype,        buffer, sizeof(int));
				memcpy(&obj_vel_axis,   buffer + sizeof(int), 3*sizeof(float));
				memcpy(&obj_accel_axis, buffer + sizeof(int) + 3*sizeof(float), 3*sizeof(float));

				std::stringstream ss;
				ss << "Received: " << objtype << ", "
									<< obj_vel_axis[0] << ", "
									<< obj_accel_axis[0];
				*/
				std::stringstream ss;
				ss << "Received: " << obj_info[0] << ", " << obj_info[1] << ", " << obj_info[2]
									<< obj_info[3] << ", " << obj_info[4] << ", " << obj_info[5];

				count = 0;

				// [todo] need to update according to the generated API ----------- END
				log_message(ss.str());
			}
        }

        close(client_socket);
        log_message("Client disconnected");
    }

    close(server_socket);
    unlink(socket_path);
}

// todo
void send_objtype(std::shared_ptr<ObjectDetectionStubImpl> myService) {
    while (true) {
		// vehicle position
		myService->fireObjectTypeEvent(objtype);

        //delay(1);
        usleep(ObjectType_interval); // 20ms
    }
}


// todo
void send_obj_vel_axis(std::shared_ptr<ObjectDetectionStubImpl> myService) {
    while (true) {
		// vehicle position
		//myService->fireObjectVelocityAxisEvent(obj_vel_axis[0], obj_vel_axis[1], obj_vel_axis[2]);
		myService->fireObjectVelocityAxisEvent(obj_info[0], obj_info[1], obj_info[2]);

        //delay(1);
        usleep(ObjectVelocityAxis_interval); // 20ms
    }
}

// todo
void send_obj_accel_axis(std::shared_ptr<ObjectDetectionStubImpl> myService) {
    while (true) {
		// vehicle angular velocity
        //myService->fireObjectAccelAxisEvent(obj_accel_axis[0], obj_accel_axis[1], obj_accel_axis[2]);
        myService->fireObjectAccelAxisEvent(obj_info[3], obj_info[4], obj_info[5]);

        //delay(1);
        usleep(ObjectAccelAxis_interval); // 20ms
    }
}
 
int main() {
	// signal handler
    signal(SIGINT, cleanup_and_exit);
    signal(SIGTERM, cleanup_and_exit);

	// set signal time interval
	std::ifstream inputFile("ObjectType_interval.txt");
    if (inputFile.is_open()) {
        inputFile >> ObjectType_interval;
        inputFile.close();
        std::cout << "Time Interval: " << ObjectType_interval << std::endl;
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

	// set signal time interval
	std::ifstream inputFile2("ObjectVelocityAxis_interval.txt");
    if (inputFile2.is_open()) {
        inputFile2 >> ObjectVelocityAxis_interval;
        inputFile2.close();
        std::cout << "Time Interval: " << ObjectVelocityAxis_interval << std::endl;
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

	// set signal time interval
	std::ifstream inputFile3("ObjectAccelAxis_interval.txt");
    if (inputFile3.is_open()) {
        inputFile3 >> ObjectAccelAxis_interval;
        inputFile3.close();
        std::cout << "Time Interval: " << ObjectAccelAxis_interval << std::endl;
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }


	// start socket thread
	std::thread socketThread(socket_thread);

	// start SOME/IP
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<ObjectDetectionStubImpl> myService = std::make_shared<ObjectDetectionStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

	// todo
	// sending thread
	//std::thread th1(send_objtype, myService);
	std::thread th2(send_obj_vel_axis, myService);
	std::thread th3(send_obj_accel_axis, myService);

    while (true) {
		std::cout << "[ObjectDetection] main thread .... time interval(1s)" << std::endl;
        delay(1);
    }
 
    return 0;
} 
