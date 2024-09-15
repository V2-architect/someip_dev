#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/IntersectionStubDefault.hpp>
#include <v1/commonapi/IntersectionStub.hpp>

class IntersectionStubImpl: public v1::commonapi::IntersectionStubDefault {
public:
    IntersectionStubImpl();
    virtual ~IntersectionStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
