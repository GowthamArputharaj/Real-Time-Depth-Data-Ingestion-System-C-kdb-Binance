#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <openssl/ssl.h>

#include <iostream>
#include <string>
#include <vector>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace ws = beast::websocket;
using tcp = asio::ip::tcp;

class WebSocket {
    asio::io_context& io;
    asio::ssl::context& ssl;
    tcp::resolver resolver;
    ws::stream<beast::ssl_stream<beast::tcp_stream>> socket;
    std::string WS_URL;
    std::string WS_PORT;
    int id = 0;

public:
    WebSocket(asio::io_context& i, asio::ssl::context& s, std::string WS_URL, std::string WS_PORT)
        : io(i), ssl(s), resolver(i), socket(i, s), WS_URL(std::move(WS_URL)), WS_PORT(std::move(WS_PORT)) {}

    void connect() {
        auto r = resolver.resolve(WS_URL, WS_PORT);
        beast::get_lowest_layer(socket).connect(r);

        SSL_set_tlsext_host_name(
            socket.next_layer().native_handle(), WS_URL.c_str());

        socket.next_layer().handshake(asio::ssl::stream_base::client);
        socket.handshake(WS_URL, "/ws");
    }

    void subscribe(const std::vector<std::string>& streams) {
        command("SUBSCRIBE", streams);
    }

    void unsubscribe(const std::vector<std::string>& streams) {
        command("UNSUBSCRIBE", streams);
    }

    std::string read() {
        beast::flat_buffer buffer;
        socket.read(buffer);
        return beast::buffers_to_string(buffer.data());
    }

private:
    void command(const std::string& method,
                 const std::vector<std::string>& streams) {
        std::string s = "{\"method\":\"" + method + "\",\"params\":[";
        for (size_t i = 0; i < streams.size(); ++i)
            s += (i ? ",\"" : "\"") + streams[i] + "\"";
        s += "],\"id\":" + std::to_string(++id) + "}";
        socket.write(asio::buffer(s));
    }
};

/*
int main() {
    asio::io_context io;
    asio::ssl::context ssl(asio::ssl::context::tls_client);
    ssl.set_default_verify_paths();
    
    string WS_URL = "stream.binance.com";
    string WS_PORT = "9443";
    WebSocket b(io, ssl, WS_URL, WS_PORT);

    b.connect();

    b.subscribe({"btcusdt@aggTrade", "ethusdt@aggTrade"});

    std::cout << b.read() << '\n';

    b.unsubscribe({"ethusdt@aggTrade"});

    std::cout << b.read() << '\n';
}
*/

