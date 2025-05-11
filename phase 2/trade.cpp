#include "Trade.hpp"
#include <ctime>
#include <cstdlib>
#include <cstring>  

Trade::Trade() : embargoCount(0) {
    marketLog.open("logs/market_log.txt", std::ios::app);
    for (int i = 0; i < MAX_EMBARGOES; ++i) {
        embargoes[i].active = false;
    }
}

Trade::~Trade() {
    if (marketLog.is_open()) marketLog.close();
}

void Trade::offerTrade(Kingdom* sender, Kingdom* receiver, const std::string& resource, int quantity, int price) {
    if (isEmbargoed(receiver->getName())) {
        std::cout << "Cannot trade with " << receiver->getName() << " due to embargo!" << std::endl;
        return;
    }
    Resource* senderRes = sender->getResource(resource);
    Resource* receiverGold = receiver->getResource("Gold");
    if (senderRes && receiverGold && senderRes->getQuantity() >= quantity && receiverGold->getQuantity() >= price) {
        senderRes->modifyQuantity(-quantity);
        receiver->addResource(new Resource(resource, quantity));
        receiverGold->modifyQuantity(-price);
        sender->addResource(new Gold(price));

       
        time_t now = time(nullptr);
        char timestamp[100];
        ctime_s(timestamp, sizeof(timestamp), &now);
        timestamp[strcspn(timestamp, "\n")] = '\0';  

        marketLog << "[" << timestamp << "] Trade: " << sender->getName() << " sent " << quantity << " " << resource
            << " to " << receiver->getName() << " for " << price << " Gold" << std::endl;
        std::cout << "Trade completed: " << sender->getName() << " -> " << receiver->getName() << std::endl;
    }
    else {
        std::cout << "Trade failed: Insufficient resources or gold!" << std::endl;
    }
}

void Trade::smuggle(Kingdom* sender, Kingdom* receiver, const std::string& resource, int quantity) {
    Resource* senderRes = sender->getResource(resource);
    if (senderRes && senderRes->getQuantity() >= quantity) {
        bool detected = (rand() % 100) < 20;
        if (detected) {
            senderRes->modifyQuantity(-quantity);
            sender->applyPolicy("morale", sender->getMorale() - 10);

          
            time_t now = time(nullptr);
            char timestamp[100];
            ctime_s(timestamp, sizeof(timestamp), &now);
            timestamp[strcspn(timestamp, "\n")] = '\0';  

            marketLog << "[" << timestamp << "] Smuggling failed: " << sender->getName() << " caught smuggling "
                << quantity << " " << resource << " to " << receiver->getName() << std::endl;
            std::cout << "Smuggling failed: Caught!" << std::endl;
        }
        else {
            senderRes->modifyQuantity(-quantity);
            receiver->addResource(new Resource(resource, quantity));

           
            time_t now = time(nullptr);
            char timestamp[100];
            ctime_s(timestamp, sizeof(timestamp), &now);
            timestamp[strcspn(timestamp, "\n")] = '\0';  

            marketLog << "[" << timestamp << "] Smuggling succeeded: " << sender->getName() << " sent " << quantity
                << " " << resource << " to " << receiver->getName() << std::endl;
            std::cout << "Smuggling succeeded!" << std::endl;
        }
    }
    else {
        std::cout << "Smuggling failed: Insufficient resources!" << std::endl;
    }
}

bool Trade::imposeEmbargo(const std::string& kingdom) {
    for (int i = 0; i < embargoCount; ++i) {
        if (embargoes[i].active && embargoes[i].kingdom == kingdom) {
            return true;
        }
    }
    if (embargoCount >= MAX_EMBARGOES) {
        std::cout << "Cannot impose embargo: Maximum limit reached!" << std::endl;
        return false;
    }
    embargoes[embargoCount] = { kingdom, true };
    embargoCount++;

    
    time_t now = time(nullptr);
    char timestamp[100];
    ctime_s(timestamp, sizeof(timestamp), &now);
    timestamp[strcspn(timestamp, "\n")] = '\0';  

    marketLog << "[" << timestamp << "] Embargo imposed on " << kingdom << std::endl;
    return true;
}

bool Trade::liftEmbargo(const std::string& kingdom) {
    for (int i = 0; i < embargoCount; ++i) {
        if (embargoes[i].active && embargoes[i].kingdom == kingdom) {
            embargoes[i].active = false;

            
            time_t now = time(nullptr);
            char timestamp[100];
            ctime_s(timestamp, sizeof(timestamp), &now);
            timestamp[strcspn(timestamp, "\n")] = '\0';  

            marketLog << "[" << timestamp << "] Embargo lifted on " << kingdom << std::endl;
            return true;
        }
    }
    return false;
}

bool Trade::isEmbargoed(const std::string& kingdom) const {
    for (int i = 0; i < embargoCount; ++i) {
        if (embargoes[i].active && embargoes[i].kingdom == kingdom) {
            return true;
        }
    }
    return false;
}
