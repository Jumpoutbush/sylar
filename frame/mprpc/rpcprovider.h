#pragma once
#include "google/protobuf/service.h"

// provide rpc service

class RpcProvider {
public:
    // release rpc service
    void NotifyService(google::protobuf::Service *service){};
};