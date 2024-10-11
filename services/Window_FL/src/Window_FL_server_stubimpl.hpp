#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Window_FLStubDefault.hpp>
#include <v1/commonapi/Window_FLStub.hpp>

class Window_FLStubImpl: public v1::commonapi::Window_FLStubDefault {
public:
    Window_FLStubImpl();
    virtual ~Window_FLStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
