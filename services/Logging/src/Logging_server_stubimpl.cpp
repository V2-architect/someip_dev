#include "Logging_server_stubimpl.hpp"

LoggingStubImpl::LoggingStubImpl() { }
LoggingStubImpl::~LoggingStubImpl() { }

// [todo] method(out)
void LoggingStubImpl::get_log_file(const std::shared_ptr<CommonAPI::ClientId> _client, get_log_fileReply_t _reply) {
	(void)_client;
	//int result = system("python3 /root/someip_app/services/Logging/send_logfile.py");
	sleep(1);
	bool response = true;
	_reply(response);
}

