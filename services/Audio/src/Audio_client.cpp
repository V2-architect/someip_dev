#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/AudioProxy.hpp>
#include <cstdlib>
#include <ctime>

using namespace v1::commonapi;


// todo
// global variables
float curr_audio_volume = 0.0;
const int32_t AUDIO_VOL_MAX = 51;
const int32_t AUDIO_CTRL_DELAY_MIN = 50;  // s

void recv_field_cb(const CommonAPI::CallStatus& callStatus, const float& val) {
    std::cout << "[Audio][Client][Field-Async] Receive callback: " << val << std::endl;
}

void handle_field_async(std::shared_ptr<AudioProxy<>> myProxy, float audio_volume) {
    CommonAPI::CallStatus callStatus;

    // [Audio] Setter Asynchronous call to set attribute of service
    CommonAPI::CallInfo info(1000);
    info.sender_ = 5678;
    std::function<void(const CommonAPI::CallStatus&, int32_t)> fcb = recv_field_cb;
    myProxy->getAudioVolumeAttribute().setValueAsync(audio_volume, fcb, &info);
}

void handle_field_sync(std::shared_ptr<AudioProxy<>> myProxy, float audio_volume) { 
	CommonAPI::CallStatus callStatus;
	CommonAPI::CallInfo info(1000);
    info.sender_ = 1234;

	float response = 0.0;
	std::cout << "[Audio][Client][Thread] Set attribute -> " << audio_volume << std::endl;
	myProxy->getAudioVolumeAttribute().setValue(audio_volume, callStatus, response, &info);
	std::cout << "[Audio][Client][Thread] Set attribute reponse -> " << response << std::endl;
}

int main(int argc, char* argv[]) {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<AudioProxy<>> myProxy = runtime->buildProxy<AudioProxy>("local", "test");

    // START modification
    // I ran into a NULL myProxy on older versions (possibly a version
    // mismatch).  Instead of segfaulting, let's note it here.  This is the
    // only change compared to the original "10 minutes" example
    if (!myProxy)
    {
       std::cerr << "[Audio][Client] FAIL: Returned  proxy is NULL! - Giving up!\n";
       return 2;
    }
    // END modification

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

	// init random seed
	std::srand(static_cast<unsigned int>(std::time(0)));

	// AudioVolume Changed Callback
    std::cout << "getAudioVolume changedEvent registration!" << std::endl;
    myProxy->getAudioVolumeAttribute().getChangedEvent().subscribe([&](const float& value) {
		curr_audio_volume = value;
        std::cout << "[Audio][Client][Main-Thread] Received change AudioVolume: " << curr_audio_volume << std::endl;
    });


	// 5sets of series of random values -----S
    const int ARRAY_SIZE = 100;
    int audio_ctrl_interval[5][ARRAY_SIZE];
	
    for (int i = 0; i < 5; ++i)
		for (int j = 0; j < ARRAY_SIZE; ++j)
			audio_ctrl_interval[i][j] = 50 + (std::rand() % 251); // 50ms ~ 300ms
	int interval_set = 0;
	int interval_idx = 0;
	// 5sets of series of random values -----E


	int audio_control_delay = 0;
	int new_audio_volume = 0;

	std::string ecu_name = argv[1];
    std::cout << "HOSTNAME: " << ecu_name << std::endl;
	if (ecu_name == "ivi") {
		std::cout << "[Audio][Client][" << ecu_name << "] while loop start" << std::endl;
		while(true) {
			std::cout << "[Audio][Client] while loop... in main thread" << std::endl;
			audio_control_delay = std::rand() % 61 + AUDIO_CTRL_DELAY_MIN; // per 50s~110s
			std::cout << "waiting until next autio_control: " << audio_control_delay << "s" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(audio_control_delay));

			while(true){
				new_audio_volume = std::rand() % AUDIO_VOL_MAX;
				if (std::abs(new_audio_volume-curr_audio_volume) > 20)
					break;
				std::cout << "new  Audio Volumn: " << new_audio_volume  << std::endl;
				std::cout << "curr Audio Volumn: " << curr_audio_volume << std::endl;
			}

			interval_set = std::rand() % 5;
			interval_idx = 0;

			if (new_audio_volume > curr_audio_volume) {
				while(curr_audio_volume < new_audio_volume) {
					handle_field_async(myProxy, ++curr_audio_volume);
					std::this_thread::sleep_for(std::chrono::milliseconds(
						audio_ctrl_interval[interval_set][interval_idx++]));
				}
			}

			else if (new_audio_volume < curr_audio_volume) {
				while(curr_audio_volume > new_audio_volume) {
					handle_field_async(myProxy, --curr_audio_volume);
					std::this_thread::sleep_for(std::chrono::milliseconds(
						audio_ctrl_interval[interval_set][interval_idx++]));
				}
			}
		}
	}
	if (ecu_name == "zone_gw_fr" || ecu_name == "zone_gw_rl" || ecu_name == "zone_gw_rr") {
		std::cout << "[Audio][Client][" << ecu_name << "] while loop start" << std::endl;
		while(true) {
			std::cout << "[Audio][Client][Only Listen] while loop... in main thread" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
    return 0;
}

