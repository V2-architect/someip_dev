#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/VehicleLocationStubDefault.hpp>
#include <v1/commonapi/VehicleLocationStub.hpp>

class VehicleLocationStubImpl: public v1::commonapi::VehicleLocationStubDefault {
public:
    VehicleLocationStubImpl();
    virtual ~VehicleLocationStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
