#include "HTTPServer.h"
#include <iostream>

void HTTPServer::establishConnection(const std::string& url) {

    std::cout << "Establishing HTTP connection to: " << url << std::endl;
}

void HTTPServer::terminateConnection(const std::string& url) {
    std::cout << "Terminating HTTP connection to: " << url << std::endl;
}