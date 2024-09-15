#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/CollisionStubDefault.hpp>
#include <v1/commonapi/CollisionStub.hpp>

class CollisionStubImpl: public v1::commonapi::CollisionStubDefault {
public:
    CollisionStubImpl();
    virtual ~CollisionStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
