#pragma once

#include <string>

class HTTPServer {
public:

    void establishConnection(const std::string& url);
    void terminateConnection(const std::string& url);

};

