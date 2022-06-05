#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <iostream>
#include <string>

class TraderWebsockets {

public:
    beast::websocket::stream<boost::asio::ssl:stream<boost::asio::ip::tcp::socket>> *ws;
    string *host;

    TraderWebsockets() {
        boost::asio::io_context ioc;
        boost::asio::ip::tcp::resolver resolver{ioc};
        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23_client);
        ctx.set_default_verify_paths();
        beast::websocket::stream<boost::asio::ssl:stream<boost::asio::ip::tcp::socket>> wss{iox, ctx};
        ws = &wss;
    };

    void connect(string *endpoint) {
        host = &endpoint;
    };

    void send(string message) {
    };

    bool connected() {
    };

    string receive() {
    };
};