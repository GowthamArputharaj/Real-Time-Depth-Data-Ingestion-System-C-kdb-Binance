#pragma once

#include <cstdint>
#include <string>
#include <string_view>

struct Depth {
    int64_t event_time;
    std::string symbol;
    int64_t received_at;
    std::string side;
    double price;
    double quantity;
};

inline std::string_view json_string(std::string_view json, std::string_view key) {
    std::string pattern = "\"" + std::string(key) + "\":\"";
    size_t start = json.find(pattern);

    if (start == std::string_view::npos)
        return {};

    start += pattern.size();

    size_t end = json.find('"', start);

    if (end == std::string_view::npos)
        return {};

    return json.substr(start, end - start);
}

inline int64_t json_int(std::string_view json, std::string_view key) {
    std::string pattern = "\"" + std::string(key) + "\":";
    size_t start = json.find(pattern);

    if (start == std::string_view::npos)
        return 0;

    start += pattern.size();

    return std::stoll(std::string(json.substr(start)));
}

inline double json_double(std::string_view json, std::string_view key) {
    std::string pattern = "\"" + std::string(key) + "\":\"";
    size_t start = json.find(pattern);

    if (start == std::string_view::npos)
        return 0.0;

    start += pattern.size();

    size_t end = json.find('"', start);

    if (end == std::string_view::npos)
        return 0.0;

    return std::stod(std::string(json.substr(start, end - start)));
}

inline bool json_bool(std::string_view json, std::string_view key) {
    std::string pattern = "\"" + std::string(key) + "\":";
    size_t start = json.find(pattern);

    if (start == std::string_view::npos)
        return false;

    start += pattern.size();

    return json.substr(start, 4) == "true";
}

inline std::vector<std::string> json_array(std::string_view json, std::string_view key) {
    std::vector<std::string> items;
    size_t start = json.find(key);
    if (start == std::string_view::npos) return items;
    
    size_t pos = json.find("[[", start);
    size_t end_all = json.find("]]", pos);
    if (pos == std::string_view::npos || end_all == std::string_view::npos) return items;
    
    pos += 1;
    while (pos < end_all) {
        size_t open_b = json.find('[', pos);
        if (open_b == std::string_view::npos || open_b > end_all) break;
        size_t close_b = json.find(']', open_b);
        
        std::string_view raw_item = json.substr(open_b + 1, close_b - open_b - 1); // e.g. "77295.00000000","5.74963000"
        size_t comma = raw_item.find(',');
        
        if (comma != std::string_view::npos) {
            // Inject fake keys so json_double can read them with "p" and "q"
            std::string formatted = "{\"p\":" + std::string(raw_item.substr(0, comma)) + 
                                    ",\"q\":" + std::string(raw_item.substr(comma + 1)) + "}";
            items.push_back(formatted);
        }
        pos = close_b + 1;
    }
    return items;
}

inline std::vector<Depth> parse_depth(std::string_view json) {
    std::vector<Depth> rows;
    
    int64_t e_time = json_int(json, "E");
    std::string sym = std::string(json_string(json, "s"));
    
    auto now = std::chrono::system_clock::now().time_since_epoch();
    int64_t recv = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();

    // Loop through bids array and extract keys natively
    auto bids = json_array(json, "\"b\":");
    for (const auto& item : bids) {
        rows.push_back(Depth{e_time, sym, recv, "buy", json_double(item, "p"), json_double(item, "q")});
    }

    // Loop through asks array and extract keys natively
    auto asks = json_array(json, "\"a\":");
    for (const auto& item : asks) {
        rows.push_back(Depth{e_time, sym, recv, "sell", json_double(item, "p"), json_double(item, "q")});
    }

    return rows;
}

/*
inline std::vector<Depth> parse_depth1(std::string_view json) {
    std::vector<Depth> rows;

    int64_t e_time = json_int(json, "E");
    std::string sym = std::string(json_string(json, "s"));
    auto now = std::chrono::system_clock::now().time_since_epoch();
    int64_t recv = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
    
    // 2. Loop through bids ("b") and add them to rows
    auto bids = json_array(json, "b");
    for (auto&& item : bids) {
        rows.push_back(Depth{e_time, sym, recv, "buy", json_double(item, 0), json_double(item, 1)});
    }

    // 3. Loop through asks ("a") and add them to rows
    auto asks = json_array(json, "a");
    for (auto&& item : asks) {
        rows.push_back(Depth{e_time, sym, recv, "sell", json_double(item, 0), json_double(item, 1)});
    }

    return rows;
}
*/

