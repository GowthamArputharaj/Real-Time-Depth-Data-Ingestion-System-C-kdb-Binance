#include "include/websocket.hpp"
#include <string>
#include <iostream>
#include "include/simdjson.h"
#include "include/parser.hpp"
#include "include/tickerplant.hpp"
#include "include/symbols.hpp"

int main() {
    // Initialize kdb+ ingestion target
    TickerPlant ticker_plant;
    if (!ticker_plant.connect("127.0.0.1", 5010)) {
        return 1;
    }
    std::cout << "TickerPlant initialized. Awaiting market feed...\n";
    
    asio::io_context io;
    asio::ssl::context ssl(asio::ssl::context::tls_client);
    ssl.set_default_verify_paths();
    
    std::string WS_URL = "stream.binance.com";
    std::string WS_PORT = "9443";
    WebSocket b(io, ssl, WS_URL, WS_PORT);

    b.connect();
    
    std::vector<std::string> symbols = get_symbols(3);
    std::cout << symbols.size();
    //return -1;
    
    b.subscribe(symbols);
    
    //for(int i = 0; i <= 9; i++) {
    while (true) {
        auto msg = b.read();
        if (msg.find("depthUpdate") == std::string::npos) {
          continue;
        }
        std::vector<Depth> updates = parse_depth(msg);
        
        // Loop over each row inside this specific packet
        for (const auto& t : updates) {
            std::cout << msg << " " << t.symbol << " " << t.price << " " << t.quantity << " " << t.side << "\n";
            
            // Forward each individual depth update row to the kdb+ engine
            if (ticker_plant.publish_depth("depth", t.event_time, t.symbol, t.received_at, t.side, t.price, t.quantity)) {
              std::cout << "Published\n";
            }
        }
        std::cout << "\n";
    }

    // std::cout << b.read() << '\n';

    b.unsubscribe(symbols);

    std::cout << b.read() << '\n';
    
}
