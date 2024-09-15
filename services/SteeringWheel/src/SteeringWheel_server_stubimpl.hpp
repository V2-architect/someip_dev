#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/SteeringWheelStubDefault.hpp>
#include <v1/commonapi/SteeringWheelStub.hpp>

class SteeringWheelStubImpl: public v1::commonapi::SteeringWheelStubDefault {
public:
    SteeringWheelStubImpl();
    virtual ~SteeringWheelStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
