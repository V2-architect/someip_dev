#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/AudioStubDefault.hpp>
#include <v1/commonapi/AudioStub.hpp>

class AudioStubImpl: public v1::commonapi::AudioStubDefault {
public:
    AudioStubImpl();
    virtual ~AudioStubImpl();
    /*
	virtual const float &getAudioVolumeAttribute() {
        return audioVolumeAttributeValue_;
    }
	*/


private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
