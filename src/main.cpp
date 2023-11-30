#include "DataStream.h"
#include "HTTPServer.h"
#include "WebSocketServer.h"

int main() {

    DataStream dataStream;
    HTTPServer httpServer;
    WebSocketServer webSocketServer;

    dataStream.sendData("Sample data");
    httpServer.terminateConnection("sample_url");
    webSocketServer.handleWebSocket("WebSocket data");

    return 0;
}
