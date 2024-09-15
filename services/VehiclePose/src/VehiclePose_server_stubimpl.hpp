#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/VehiclePoseStubDefault.hpp>
#include <v1/commonapi/VehiclePoseStub.hpp>

class VehiclePoseStubImpl: public v1::commonapi::VehiclePoseStubDefault {
public:
    VehiclePoseStubImpl();
    virtual ~VehiclePoseStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
