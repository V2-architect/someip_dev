#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Window_FRStubDefault.hpp>
#include <v1/commonapi/Window_FRStub.hpp>

class Window_FRStubImpl: public v1::commonapi::Window_FRStubDefault {
public:
    Window_FRStubImpl();
    virtual ~Window_FRStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
