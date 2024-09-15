#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/TransmissionStubDefault.hpp>
#include <v1/commonapi/TransmissionStub.hpp>

class TransmissionStubImpl: public v1::commonapi::TransmissionStubDefault {
public:
    TransmissionStubImpl();
    virtual ~TransmissionStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
