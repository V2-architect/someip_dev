#ifndef SOMEIPSERVICESTUBIMPL_H_
#define SOMEIPSERVICESTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/LoggingStubDefault.hpp>
#include <v1/commonapi/LoggingStub.hpp>
#include <unistd.h>

class LoggingStubImpl: public v1::commonapi::LoggingStubDefault {
public:
    LoggingStubImpl();
    virtual ~LoggingStubImpl();

    // [todo] method definition
	virtual void get_log_file(const std::shared_ptr<CommonAPI::ClientId> _client, get_log_fileReply_t _reply);
private:
};



#endif /* SOMEIPSERVICESTUBIMPL_H_ */
