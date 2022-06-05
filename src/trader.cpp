#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <iostream>

namespace beast     = boost::beast;
namespace http      = beast::http;
namespace websocket = beast::websocket;
namespace net       = boost::asio;
namespace ssl       = net::ssl;
namespace json      = boost::json;

using tcp = boost::asio::ip::tcp;
using namespace std;

int main() {
    cout << "testing remote acces" << endl;
    string host = "ws-feed.exchange.coinbase.com";
    auto const  port = "443";

    json::value doc = {
        {"type", "subscribe"},
        {"product_ids", {"ETH-USD"}},
        {"channels", {"matches"}},
    };

    net::io_context ioc;
    tcp::resolver   resolver{ioc};
    ssl::context    ctx(ssl::context::sslv23_client);
    ctx.set_default_verify_paths();
    websocket::stream<ssl::stream<tcp::socket>> ws{ioc, ctx};

    auto const results = resolver.resolve(host, port);

    // connect raw socket
    auto& raw = beast::get_lowest_layer(ws);
    auto ep = net::connect(raw, results);

    // ssl handshake
    if (!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str())) {
        throw boost::system::system_error(
            ::ERR_get_error(), boost::asio::error::get_ssl_category());
    }
    ws.next_layer().handshake(ssl::stream_base::client);

    host += ":" + std::to_string(ep.port());

    ws.set_option(
        websocket::stream_base::decorator([](websocket::request_type& req) {
            req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
        }));

    websocket::permessage_deflate per_def;
    per_def.client_enable = true;

    ws.set_option(per_def);

    // websocket handshake
    ws.handshake(host, "/");

    ws.write(net::buffer(serialize(doc)));

    beast::flat_buffer buffer;

    int i = 0;
    while(i < 20) {
        ws.read(buffer);
        cout << beast::make_printable(buffer.data()) << std::endl;
        buffer.consume(buffer.size());
        i++;
    } // while

    ws.close(websocket::close_code::normal);
}
