#ifndef EVENTAPPSTUBIMPL_H_
#define EVENTAPPSTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/EventAppStubDefault.hpp>
#include <v1/commonapi/EventAppStub.hpp>

class EventAppStubImpl: public v1::commonapi::EventAppStubDefault {
public:
    EventAppStubImpl();
    virtual ~EventAppStubImpl();

    virtual bool onEvent004SelectiveSubscriptionRequested(const std::shared_ptr<CommonAPI::ClientId> _client);
    virtual void onEvent004SelectiveSubscriptionChanged(const std::shared_ptr<CommonAPI::ClientId> _client, const CommonAPI::SelectiveBroadcastSubscriptionEvent _event);

    virtual bool onEvent005SelectiveSubscriptionRequested(const std::shared_ptr<CommonAPI::ClientId> _client);
    virtual void onEvent005SelectiveSubscriptionChanged(const std::shared_ptr<CommonAPI::ClientId> _client, const CommonAPI::SelectiveBroadcastSubscriptionEvent _event);

    virtual bool onEvent006SelectiveSubscriptionRequested(const std::shared_ptr<CommonAPI::ClientId> _client);
    virtual void onEvent006SelectiveSubscriptionChanged(const std::shared_ptr<CommonAPI::ClientId> _client, const CommonAPI::SelectiveBroadcastSubscriptionEvent _event);


private:
};

#endif /* EVENTAPPSTUBIMPL_H_ */
