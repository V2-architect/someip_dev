#ifndef METHODAPPSTUBIMPL_H_
#define METHODAPPSTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/MethodAppStubDefault.hpp>
#include <v1/commonapi/MethodAppStub.hpp>

class MethodAppStubImpl: public v1::commonapi::MethodAppStubDefault {
public:
    MethodAppStubImpl();
    virtual ~MethodAppStubImpl();
    virtual void method001(const std::shared_ptr<CommonAPI::ClientId> _client, method001Reply_t _reply);
    virtual void method002(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _in1, method002Reply_t _reply);
    virtual void method003(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _in1, method003Reply_t _reply);
private:
};

#endif /* METHODAPPSTUBIMPL_H_ */
