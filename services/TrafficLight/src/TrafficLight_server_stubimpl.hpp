#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/TrafficLightStubDefault.hpp>
#include <v1/commonapi/TrafficLightStub.hpp>

class TrafficLightStubImpl: public v1::commonapi::TrafficLightStubDefault {
public:
    TrafficLightStubImpl();
    virtual ~TrafficLightStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
