CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -I/opt/boost -Iinclude

LDLIBS = -lssl -lcrypto -pthread

KDB_OBJ = lib/c.o

binance: main.cpp include/websocket.hpp include/parser.hpp include/simdjson.cpp include/simdjson.h
	$(CXX) $(CXXFLAGS) main.cpp include/simdjson.cpp $(KDB_OBJ) -o binance $(LDLIBS)

clean:
	rm -f binance
