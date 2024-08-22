#ifndef VEHICLESPEEDSTUBIMPL_H_
#define VEHICLESPEEDSTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/VehicleSpeedStubDefault.hpp>
#include <v1/commonapi/VehicleSpeedStub.hpp>

class VehicleSpeedStubImpl: public v1::commonapi::VehicleSpeedStubDefault {
public:
    VehicleSpeedStubImpl();
    virtual ~VehicleSpeedStubImpl();

private:
};

#endif /* EVENTAPPSTUBIMPL_H_ */
