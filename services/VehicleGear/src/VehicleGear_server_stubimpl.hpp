#ifndef VEHICLEGEARSTUBIMPL_H_
#define VEHICLEGEARSTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/VehicleGearStubDefault.hpp>
#include <v1/commonapi/VehicleGearStub.hpp>

class VehicleGearStubImpl: public v1::commonapi::VehicleGearStubDefault {
public:
    VehicleGearStubImpl();
    virtual ~VehicleGearStubImpl();

private:
};

#endif /* EVENTAPPSTUBIMPL_H_ */
