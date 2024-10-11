#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Window_RRStubDefault.hpp>
#include <v1/commonapi/Window_RRStub.hpp>

class Window_RRStubImpl: public v1::commonapi::Window_RRStubDefault {
public:
    Window_RRStubImpl();
    virtual ~Window_RRStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
