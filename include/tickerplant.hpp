#pragma once

#include <iostream>
#include <string>

// Define the KX C API version prior to inclusion
#define KXVER 3
#include "k.h"

class TickerPlant {
private:
    int kdb_handle;
    std::string host;
    int port;

public:
    TickerPlant() : kdb_handle(0), host(""), port(0) {}

    ~TickerPlant() {
        disconnect();
    }

    // Connect to a running kdb+ tickerplant or data ingestion process
    bool connect(const std::string& target_host, int target_port) {
        host = target_host;
        port = target_port;

        // khpu connects via host, port, and "username:password" credentials
        kdb_handle = khpu(const_cast<char*>(host.c_str()), port, const_cast<char*>(""));
        
        if (kdb_handle < 0) {
            std::cerr << "Connection error: Failed to connect to kdb+ at " << host << ":" << port << "\n";
            return false;
        } else if (kdb_handle == 0) {
            std::cerr << "Authentication error: Access denied by kdb+ process.\n";
            return false;
        }

        std::cout << "TickerPlant connected to kdb+ at " << host << ":" << port << " (Handle: " << kdb_handle << ")\n";
        return true;
    }

    // Explicitly disconnect and release the network socket
    void disconnect() {
        if (kdb_handle > 0) {
            kclose(kdb_handle);
            std::cout << "TickerPlant disconnected from kdb+ (Handle: " << kdb_handle << ")\n";
            kdb_handle = 0;
        }
    }

    // Updated to handle all 7 parameters required by your depth schema
    bool publish_depth(const std::string& table_name, long long event_time, const std::string& symbol, long long received_at, const std::string& side, double price, double quantity) {
        if (kdb_handle <= 0) {
            std::cerr << "Publish error: Active connection to kdb+ is unavailable.\n";
            return false;
        }
        
        // 1. Math calculation to fix the 1970(30 year offset) timestamp bug
        long long kdb_offset_ns = 946684800000000000LL;
        long long kdb_received_at = received_at - kdb_offset_ns;
        long long kdb_offset_ms = 946684800000LL;
        long long kdb_event_time = (event_time - kdb_offset_ms);// * 1000000LL;

        // Construct a kdb+ mixed list representing the row payload structure
        K row = knk(6, 
            kj(kdb_event_time),                        // Event Time long long
            ks(const_cast<char*>(symbol.c_str())), // Symbol -> KS
            //kj(kdb_received_at),
            ktj(-KP, kdb_received_at),
            ks(const_cast<char*>(side.c_str())),
            kf(price),                             // Price -> KF
            kf(quantity)                              // Size -> KF
        );
        
        // Async payload transmission using the negative handle mechanism
        K result = k(-kdb_handle, const_cast<char*>(".u.upd"), ks(const_cast<char*>(table_name.c_str())), row, (K)0);
        
        // 0 means immediate success. If it's a valid pointer, ensure it is not an error object (type -128)
        if (result == (K)0) {
            return true;
        }
        
        if (result->t == -128) {
            std::cerr << "kdb+ Asynchronous Network Error: " << result->s << "\n";
            r0(result); // Must free the error object to avoid memory leaks!
            return false;
        }

        // If it returned a valid object but not an error, the write succeeded into network buffer
        return true;
    }


    int get_handle() const { return kdb_handle; }
};

