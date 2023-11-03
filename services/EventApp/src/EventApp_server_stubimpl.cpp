#include "EventApp_server_stubimpl.hpp"

EventAppStubImpl::EventAppStubImpl() { }
EventAppStubImpl::~EventAppStubImpl() { }


// Selective Event4
bool EventAppStubImpl::onEvent004SelectiveSubscriptionRequested(const std::shared_ptr<CommonAPI::ClientId> _client) {
    std::cout << "[EventApp] onEvent004SelectiveSubscriptionRequested called" << std::endl;
    return true;
}

void EventAppStubImpl::onEvent004SelectiveSubscriptionChanged(const std::shared_ptr<CommonAPI::ClientId> _client, const CommonAPI::SelectiveBroadcastSubscriptionEvent _event) {
    std::cout << "[EventApp] onEvent004SelectiveSubscriptionChanged called" << std::endl;
}


// Selective Event5
bool EventAppStubImpl::onEvent005SelectiveSubscriptionRequested(const std::shared_ptr<CommonAPI::ClientId> _client) {
    std::cout << "[EventApp] onEvent005SelectiveSubscriptionRequested called" << std::endl;
    return true;
}

void EventAppStubImpl::onEvent005SelectiveSubscriptionChanged(const std::shared_ptr<CommonAPI::ClientId> _client, const CommonAPI::SelectiveBroadcastSubscriptionEvent _event) {
    std::cout << "[EventApp] onEvent005SelectiveSubscriptionChanged called" << std::endl;
}


// Selective Event6
bool EventAppStubImpl::onEvent006SelectiveSubscriptionRequested(const std::shared_ptr<CommonAPI::ClientId> _client) {
    std::cout << "[EventApp] onEvent006SelectiveSubscriptionRequested called" << std::endl;
    return true;
}

void EventAppStubImpl::onEvent006SelectiveSubscriptionChanged(const std::shared_ptr<CommonAPI::ClientId> _client, const CommonAPI::SelectiveBroadcastSubscriptionEvent _event) {
    std::cout << "[EventApp] onEvent006SelectiveSubscriptionChanged called" << std::endl;
}
