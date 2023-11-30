#include "HTTPServer.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

void HTTPServer::establishStreamingConnection(const std::string &producerId,const std::vector<StreamInfo> &streamInfoList) {

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::beast::tcp_stream stream(io_context);

    // Realizarea cererii POST către Consumer
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("consumer_address", "http");
    stream.connect(endpoints);

    // Construirea și trimiterea cererii HTTP POST
    std::string postBody = "producerId=" + producerId + "&streamInfoList=..."; // Construiește corpul cererii conform specificațiilor
    boost::beast::http::request<boost::beast::http::string_body> postReq(boost::beast::http::verb::post, "/connections", 11);
    postReq.set(boost::beast::http::field::host, "consumer_address");
    postReq.set(boost::beast::http::field::user_agent, "Boost HTTP Client");
    postReq.set(boost::beast::http::field::content_type, "application/x-www-form-urlencoded");
    postReq.body() = postBody;
    postReq.prepare_payload();

    boost::beast::http::write(stream, postReq);

    // Primește și interpretează răspunsul POST
    boost::beast::flat_buffer buffer;
    boost::beast::http::response<boost::beast::http::string_body> postRes;
    boost::beast::http::read(stream, buffer, postRes);

    if (postRes.result() == boost::beast::http::status::created) {
        // Extrage connectionId din răspuns
        std::string location = boost::beast::http::to_string(postRes[boost::beast::http::field::location]);
        std::size_t found = location.find_last_of('/');
        std::string connectionId = location.substr(found + 1);

        // Construirea și trimiterea cererii HTTP GET
        boost::beast::http::request<boost::beast::http::empty_body> getReq(boost::beast::http::verb::get, "/connections/" + connectionId, 11);
        getReq.set(boost::beast::http::field::host, "consumer_address");
        getReq.set(boost::beast::http::field::user_agent, "Boost HTTP Client");

        boost::beast::http::write(stream, getReq);

        // Primește și interpretează răspunsul GET
        boost::beast::http::response<boost::beast::http::string_body> getRes;
        boost::beast::http::read(stream, buffer, getRes);

        if (getRes.result() == boost::beast::http::status::switching_protocols) {
            std::string secWebSocketAccept = boost::beast::http::to_string(getRes[boost::beast::http::field::sec_websocket_accept]);
            std::cout << "Connection established with WebSocket. Sec-WebSocket-Accept: " << secWebSocketAccept << std::endl;
        }
    }

}

void HTTPServer::terminateConnection(const std::string& url) {
    std::cout << "Terminating HTTP connection to: " << url << std::endl;
}