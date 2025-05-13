#include "Stronghold.h"
#include <sstream> 

Trade::Trade() : offerCount(0), offerCapacity(50) {
    offers = new TradeOffer[offerCapacity];
}

Trade::~Trade() {
    delete[] offers;
}

void Trade::createOffer(const string& from, const string& to, const string& resource, double amount, double price) {
    if (amount <= 0 || price < 0)
        throw CustomException("Invalid trade parameters");
    if (offerCount >= offerCapacity)
        throw CustomException("Offer capacity exceeded");

    std::stringstream ss;
    ss << from << "_" << offerCount;

    offers[offerCount].from = from;
    offers[offerCount].to = to;
    offers[offerCount].resource = resource;
    offers[offerCount].amount = amount;
    offers[offerCount].price = price;
    offers[offerCount].id = ss.str();

    offerCount++;
}

bool Trade::acceptOffer(const string& kingdom, const string& offerId, ResourceManager<double>& resources) {
    for (int i = 0; i < offerCount; i++) {
        if (offers[i].id == offerId && offers[i].to == kingdom) {
            try {
                resources.consumeResource("gold", offers[i].price);
                resources.addResource(offers[i].resource, offers[i].amount);
                offers[i] = offers[--offerCount];  
                return true;
            }
            catch (const CustomException&) {
                return false;
            }
        }
    }
    return false;
}
