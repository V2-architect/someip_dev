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

// [example]: const char* socket_path = "/root/someip_app/tmp/uds_vehicle_speed";
const char* socket_path = "@UNIX_DOMAIN_SOCKET_PATH@";
int server_socket = -1;
std::atomic<bool> running(true);

// [todo] need to update according to the generated API
// [todo] shared data(global variable) between socket thread and main thread
float vehicle_speed_data[3] = {0.0, 0.0, 0.0};

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
            // [todo] need to update according to the generated API ----------- START
            ssize_t bytes_received = recv(client_socket, vehicle_speed_data, sizeof(vehicle_speed_data), 0);
            if (bytes_received <= 0) {
                break;
            }

            std::stringstream ss;
            ss << "Received: " << vehicle_speed_data[0] << ", " << vehicle_speed_data[1] << ", " << vehicle_speed_data[2];
            // [todo] need to update according to the generated API ----------- END
            log_message(ss.str());
        }

        close(client_socket);
        log_message("Client disconnected");
    }

    close(server_socket);
    unlink(socket_path);
}
 
int main() {
	// signal handler
    signal(SIGINT, cleanup_and_exit);
    signal(SIGTERM, cleanup_and_exit);

	// start socket thread
	std::thread socketThread(socket_thread);

	// start SOME/IP
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<@SERVICE_NAME@StubImpl> myService = std::make_shared<@SERVICE_NAME@StubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    while (true) {
        std::cout << "[@SERVICE_NAME@] sleep 2s" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
} 
