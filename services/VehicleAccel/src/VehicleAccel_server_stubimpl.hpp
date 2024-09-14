#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/VehicleAccelStubDefault.hpp>
#include <v1/commonapi/VehicleAccelStub.hpp>

class VehicleAccelStubImpl: public v1::commonapi::VehicleAccelStubDefault {
public:
    VehicleAccelStubImpl();
    virtual ~VehicleAccelStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
