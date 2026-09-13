#pragma once

#include <string>
#include <vector>


const std::vector<std::string> all_binance_symbols1 = {"btcusdt@depth@100ms"};
// 1. Simple list of 100 symbols using standard strings
const std::vector<std::string> all_binance_symbols = {
    "btcusdt@depth@100ms", "ethusdt@depth@100ms", "solusdt@depth@100ms", "xrpusdt@depth@100ms",
    "bnbusdt@depth@100ms", "adausdt@depth@100ms", "dogeusdt@depth@100ms", "avaxusdt@depth@100ms",
    "dotusdt@depth@100ms", "maticusdt@depth@100ms", "linkusdt@depth@100ms", "ltcusdt@depth@100ms",
    "shibusdt@depth@100ms", "trxusdt@depth@100ms", "bchusdt@depth@100ms", "xlmusdt@depth@100ms",
    "atomusdt@depth@100ms", "xplusdt@depth@100ms", "filusdt@depth@100ms", "aptusdt@depth@100ms",
    "nearusdt@depth@100ms", "ldousdt@depth@100ms", "arbusdt@depth@100ms", "opusdt@depth@100ms",
    "grtusdt@depth@100ms", "ftmusdt@depth@100ms", "mkrusdt@depth@100ms", "crvusdt@depth@100ms",
    "gmxusdt@depth@100ms", "dydxusdt@depth@100ms", "injusdt@depth@100ms", "rndrusdt@depth@100ms",
    "woousdt@depth@100ms", "oceanusdt@depth@100ms", "fetusdt@depth@100ms", "agixusdt@depth@100ms",
    "stxusdt@depth@100ms", "imxusdt@depth@100ms", "flowusdt@depth@100ms", "chzusdt@depth@100ms",
    "galausdt@depth@100ms", "axsusdt@depth@100ms", "sandusdt@depth@100ms", "manadusdt@depth@100ms",
    "apeusdt@depth@100ms", "thetausdt@depth@100ms", "egldusdt@depth@100ms", "aaveusdt@depth@100ms",
    "rleusdt@depth@100ms", "compusdt@depth@100ms", "snxusdt@depth@100ms", "1inchusdt@depth@100ms",
    "cakeusdt@depth@100ms", "sushiusdt@depth@100ms", "yfiusdt@depth@100ms", "crvusdt@depth@100ms",
    "enjusdt@depth@100ms", "lrcusdt@depth@100ms", "ankrusdt@depth@100ms", "maskusdt@depth@100ms",
    "qtumusdt@depth@100ms", "eosusdt@depth@100ms", "neousdt@depth@100ms", "vetusdt@depth@100ms",
    "icpusdt@depth@100ms", "filusdt@depth@100ms", "etcusdt@depth@100ms", "zecusdt@depth@100ms",
    "dashusdt@depth@100ms", "xmrusdt@depth@100ms", "wavesusdt@depth@100ms", "zilusdt@depth@100ms",
    "hotusdt@depth@100ms", "btgusdt@depth@100ms", "iotausdt@depth@100ms", "omgusdt@depth@100ms",
    "bntusdt@depth@100ms", "kncusdt@depth@100ms", "renusdt@depth@100ms", "zrxusdt@depth@100ms",
    "lrcusdt@depth@100ms", "balusdt@depth@100ms", "audiousdt@depth@100ms", "bandusdt@depth@100ms",
    "oceanusdt@depth@100ms", "rlcusdt@depth@100ms", "ctsiusdt@depth@100ms", "stmxusdt@depth@100ms",
    "sklusdt@depth@100ms", "hiveusdt@depth@100ms", "scusdt@depth@100ms", "oneusdt@depth@100ms",
    "celousdt@depth@100ms", "roseusdt@depth@100ms", "bicousdt@depth@100ms", "glmrusdt@depth@100ms",
    "movrusdt@depth@100ms", "kavausdt@depth@100ms", "minausdt@depth@100ms", "woousdt@depth@100ms"
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

