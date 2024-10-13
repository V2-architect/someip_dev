#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Window_RLStubDefault.hpp>
#include <v1/commonapi/Window_RLStub.hpp>

class Window_RLStubImpl: public v1::commonapi::Window_RLStubDefault {
public:
    Window_RLStubImpl();
    virtual ~Window_RLStubImpl();

private:
};

#endif /* SOMEIPSERVICESTUBIMPL_H_ */
