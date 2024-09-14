#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/@SERVICE_NAME@StubDefault.hpp>
#include <v1/commonapi/@SERVICE_NAME@Stub.hpp>

class @SERVICE_NAME@StubImpl: public v1::commonapi::@SERVICE_NAME@StubDefault {
public:
    @SERVICE_NAME@StubImpl();
    virtual ~@SERVICE_NAME@StubImpl();

    // [todo] method definition
    virtual void @METHOD_NAME@(const std::shared_ptr<CommonAPI::ClientId> _client, method001Reply_t _reply);
    virtual void @METHOD_NAME@(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _in1, method002Reply_t _reply);
    virtual void @METHOD_NAME@(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _in1, method003Reply_t _reply);
private:
};



#endif /* SOMEIPSERVICESTUBIMPL_H_ */
