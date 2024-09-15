#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/DrivingStubDefault.hpp>
#include <v1/commonapi/DrivingStub.hpp>

class DrivingStubImpl: public v1::commonapi::DrivingStubDefault {
public:
    DrivingStubImpl();
    virtual ~DrivingStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
