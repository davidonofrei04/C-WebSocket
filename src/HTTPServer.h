#pragma once

#include <string>

struct StreamInfo {
    std::string streamType;
    std::string serializationFormat;
    std::string streamID;
    std::string objectAddress;
    std::vector<std::string> performanceMetrics;
    std::string jobID;
};

class HTTPServer {
public:

    void establishStreamingConnection(const std::string& producerId, const std::vector<StreamInfo>& streamInfoList);
    void terminateConnection(const std::string& url);

};