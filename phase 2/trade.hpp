#ifndef TRADE_HPP
#define TRADE_HPP

#include "Kingdom.hpp"
#include <string>
#include <fstream>

class Trade {
private:
    static const int MAX_EMBARGOES = 10;
    struct Embargo {
        std::string kingdom;
        bool active;
    };
    std::ofstream marketLog;
    Embargo embargoes[MAX_EMBARGOES];
    int embargoCount;
public:
    Trade();
    ~Trade();
    void offerTrade(Kingdom* sender, Kingdom* receiver, const std::string& resource, int quantity, int price);
    void smuggle(Kingdom* sender, Kingdom* receiver, const std::string& resource, int quantity);
    bool imposeEmbargo(const std::string& kingdom);
    bool liftEmbargo(const std::string& kingdom);
    bool isEmbargoed(const std::string& kingdom) const;
};

#endif 