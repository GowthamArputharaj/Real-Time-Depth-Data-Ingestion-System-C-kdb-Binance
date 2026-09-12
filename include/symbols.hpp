#pragma once

#include <string>
#include <vector>


const std::vector<std::string> all_binance_symbols = {"btcusdt@depth@100ms"};
// 1. Simple list of 100 symbols using standard strings
const std::vector<std::string> all_binance_symbols1 = {
    "btcusdt@aggTrade", "ethusdt@aggTrade", "solusdt@aggTrade", "xrpusdt@aggTrade",
    "bnbusdt@aggTrade", "adausdt@aggTrade", "dogeusdt@aggTrade", "avaxusdt@aggTrade",
    "dotusdt@aggTrade", "maticusdt@aggTrade", "linkusdt@aggTrade", "ltcusdt@aggTrade",
    "shibusdt@aggTrade", "trxusdt@aggTrade", "bchusdt@aggTrade", "xlmusdt@aggTrade",
    "atomusdt@aggTrade", "xplusdt@aggTrade", "filusdt@aggTrade", "aptusdt@aggTrade",
    "nearusdt@aggTrade", "ldousdt@aggTrade", "arbusdt@aggTrade", "opusdt@aggTrade",
    "grtusdt@aggTrade", "ftmusdt@aggTrade", "mkrusdt@aggTrade", "crvusdt@aggTrade",
    "gmxusdt@aggTrade", "dydxusdt@aggTrade", "injusdt@aggTrade", "rndrusdt@aggTrade",
    "woousdt@aggTrade", "oceanusdt@aggTrade", "fetusdt@aggTrade", "agixusdt@aggTrade",
    "stxusdt@aggTrade", "imxusdt@aggTrade", "flowusdt@aggTrade", "chzusdt@aggTrade",
    "galausdt@aggTrade", "axsusdt@aggTrade", "sandusdt@aggTrade", "manadusdt@aggTrade",
    "apeusdt@aggTrade", "thetausdt@aggTrade", "egldusdt@aggTrade", "aaveusdt@aggTrade",
    "rleusdt@aggTrade", "compusdt@aggTrade", "snxusdt@aggTrade", "1inchusdt@aggTrade",
    "cakeusdt@aggTrade", "sushiusdt@aggTrade", "yfiusdt@aggTrade", "crvusdt@aggTrade",
    "enjusdt@aggTrade", "lrcusdt@aggTrade", "ankrusdt@aggTrade", "maskusdt@aggTrade",
    "qtumusdt@aggTrade", "eosusdt@aggTrade", "neousdt@aggTrade", "vetusdt@aggTrade",
    "icpusdt@aggTrade", "filusdt@aggTrade", "etcusdt@aggTrade", "zecusdt@aggTrade",
    "dashusdt@aggTrade", "xmrusdt@aggTrade", "wavesusdt@aggTrade", "zilusdt@aggTrade",
    "hotusdt@aggTrade", "btgusdt@aggTrade", "iotausdt@aggTrade", "omgusdt@aggTrade",
    "bntusdt@aggTrade", "kncusdt@aggTrade", "renusdt@aggTrade", "zrxusdt@aggTrade",
    "lrcusdt@aggTrade", "balusdt@aggTrade", "audiousdt@aggTrade", "bandusdt@aggTrade",
    "oceanusdt@aggTrade", "rlcusdt@aggTrade", "ctsiusdt@aggTrade", "stmxusdt@aggTrade",
    "sklusdt@aggTrade", "hiveusdt@aggTrade", "scusdt@aggTrade", "oneusdt@aggTrade",
    "celousdt@aggTrade", "roseusdt@aggTrade", "bicousdt@aggTrade", "glmrusdt@aggTrade",
    "movrusdt@aggTrade", "kavausdt@aggTrade", "minausdt@aggTrade", "woousdt@aggTrade"
};

// 2. Simple slicing function that returns the first N strings
inline std::vector<std::string> get_symbols(size_t n) {
    return all_binance_symbols;
    if (n > all_binance_symbols.size()) {
        n = all_binance_symbols.size();
    }
    
    // Copy the first N elements into a new vector using standard iterators
    return std::vector<std::string>(all_binance_symbols.begin(), all_binance_symbols.begin() + n);
}

