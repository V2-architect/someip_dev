#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/@SERVICE_NAME@StubDefault.hpp>
#include <v1/commonapi/@SERVICE_NAME@Stub.hpp>

class @SERVICE_NAME@StubImpl: public v1::commonapi::@SERVICE_NAME@StubDefault {
public:
    @SERVICE_NAME@StubImpl();
    virtual ~@SERVICE_NAME@StubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
