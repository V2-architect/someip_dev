#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ObjectDetectionStubDefault.hpp>
#include <v1/commonapi/ObjectDetectionStub.hpp>

class ObjectDetectionStubImpl: public v1::commonapi::ObjectDetectionStubDefault {
public:
    ObjectDetectionStubImpl();
    virtual ~ObjectDetectionStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
