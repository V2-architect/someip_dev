#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/HelloWorldStubDefault.hpp>

class HelloWorldStubImpl: public v1::commonapi::HelloWorldStubDefault {
public:
    HelloWorldStubImpl();
    virtual ~HelloWorldStubImpl();
    virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _return);

    //virtual const int32_t& getXAttribute();
    /*
    virtual const int32_t& getXAttribute();
    virtual const int32_t& getXAttribute(const std::shared_ptr<CommonAPI::ClientId> _client);
    virtual void setXAttribute(int32_t _value);
    virtual void setXAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _value);
    */
    virtual void fireLocationChangedEvent(const int32_t &_loc) {
        HelloWorldStub::fireLocationChangedEvent(_loc);
    }

    virtual void sayHelloFnF(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name);

    //int32_t tmp = 0;
private:
};
#endif /* HELLOWORLDSTUBIMPL_H_ */
