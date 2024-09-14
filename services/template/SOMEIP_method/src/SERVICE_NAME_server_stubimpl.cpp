#include "@SERVICE_NAME@_server_stubimpl.hpp"

@SERVICE_NAME@StubImpl::@SERVICE_NAME@StubImpl() { }
@SERVICE_NAME@StubImpl::~@SERVICE_NAME@StubImpl() { }

// [todo] method(out)
void @SERVICE_NAME@StubImpl::@METHOD_NAME@(const std::shared_ptr<CommonAPI::ClientId> _client, method001Reply_t _reply) {
    std::cout << "Called method001(only out)" << std::endl;
    std::cout << "  => return 100" << std::endl;
    int32_t val = 100;
	_reply(val);
}  

// [todo] method(in)
void @SERVICE_NAME@StubImpl::@METHOD_NAME@(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _in1, method002Reply_t _reply) {
    std::cout << "Called method002(only in)" << std::endl;
}  

// [todo] method(in/out)
void @SERVICE_NAME@StubImpl::@METHOD_NAME@(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _in1, method003Reply_t _reply) {
    std::cout << "Called method003(in/out)" << std::endl;
    std::cout << "  => in: " << _in1 << std::endl;
    std::cout << "  => return 100" << std::endl;
    int32_t val = 100;
	_reply(val);
}

