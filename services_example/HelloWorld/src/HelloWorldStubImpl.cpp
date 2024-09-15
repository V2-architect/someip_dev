#include "HelloWorldStubImpl.hpp"

HelloWorldStubImpl::HelloWorldStubImpl() { }
HelloWorldStubImpl::~HelloWorldStubImpl() { }

void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _reply) {
    std::cout << "Received 'sayHello(sync)' request" << std::endl;
    std::cout << "   2s delay started!" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "   2s delay finished!" << std::endl;

    std::stringstream messageStream;
    messageStream << "Hello " << _name << "!";
    std::cout << "sayHello('" << _name << "'): '" << messageStream.str() << "'\n";

    _reply(messageStream.str());
};

void HelloWorldStubImpl::sayHelloFnF(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name) {
    std::cout << "Received 'sayHello(FireAndForget sync)' request" << std::endl;

    std::stringstream messageStream;
    messageStream << "Hello " << _name << "!";
    std::cout << "sayHello('" << _name << "'): '" << messageStream.str() << "'\n";
}

/*
const int32_t& HelloWorldStubImpl::getXAttribute() {
    tmp += 1;
    return std::move(tmp);
}
*/
