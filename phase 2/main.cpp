#include "Kingdom.hpp"
#include "Communication.hpp"
#include "Alliance.hpp"
#include "Trade.hpp"
#include "Conflict.hpp"
#include "Map.hpp"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>

int main() {
    srand(time(nullptr));
    std::ofstream gameLog("logs/game_session_log.txt", std::ios::app);

    // Secure timestamp
    time_t now = time(nullptr);
    char startBuffer[100];
    ctime_s(startBuffer, sizeof(startBuffer), &now);
    startBuffer[strcspn(startBuffer, "\n")] = '\0'; // remove newline
    gameLog << "=== Game Session Started: " << startBuffer << " ===" << std::endl;

    Kingdom k1("Aragon", 1000, 80, 200);
    k1.addResource(new Food(500));
    k1.addResource(new Gold(300));

    Kingdom k2("Bavaria", 1200, 75, 250);
    k2.addResource(new Food(600));
    k2.addResource(new Gold(250));

    Kingdom k3("Caledonia", 900, 85, 180);
    k3.addResource(new Food(450));
    k3.addResource(new Gold(350));

    Communication comm;
    Alliance alliances;
    Trade trade;
    Conflict conflict;
    Map map;

    map.placeKingdom("Aragon", 0, 0);
    map.placeKingdom("Bavaria", 2, 2);
    map.placeKingdom("Caledonia", 4, 4);
    gameLog << "Kingdoms placed on map\n";
    map.display();

    for (int turn = 1; turn <= 3; ++turn) {
        gameLog << "\n=== Turn " << turn << " ===\n";

        k1.updateEconomy();
        k1.updatePopulation();
        k1.updateArmy();
        k2.updateEconomy();
        k2.updatePopulation();
        k2.updateArmy();
        k3.updateEconomy();
        k3.updatePopulation();
        k3.updateArmy();
        gameLog << "Kingdoms updated: Economy, Population, Army\n";

        comm.sendMessage("Aragon", "Bavaria", "Propose a peace treaty for 5 turns?");
        comm.sendMessage("Bavaria", "Aragon", "Agreed!");
        comm.sendMessage("Caledonia", "Aragon", "Beware, I’m watching you.");
        gameLog << "Messages exchanged\n";

        alliances.formTreaty("Aragon", "Bavaria", "Peace", 5);
        alliances.updateTreaties();
        gameLog << "Treaty formed: Aragon-Bavaria\n";

        trade.offerTrade(&k1, &k2, "Food", 100, 50);
        trade.smuggle(&k3, &k2, "Gold", 30);
        trade.imposeEmbargo("Caledonia");
        gameLog << "Trade and smuggling attempted\n";

        conflict.attack(&k3, &k2, &alliances);
        conflict.surpriseAttack(&k2, &k1, &alliances);
        gameLog << "Conflicts resolved\n";

        map.moveKingdom("Aragon", 1, 1);
        gameLog << "Aragon moved\n";

        std::cout << "\nTurn " << turn << " State:\n";
        k1.display();
        k2.display();
        k3.display();
        alliances.displayTreaties();
        map.display();
    }

    std::cout << "\nChat Log:\n";
    comm.displayMessages();

    gameLog << "Session completed\n";

    // Secure end time
    time_t endTime = time(nullptr);
    char endBuffer[100];
    ctime_s(endBuffer, sizeof(endBuffer), &endTime);
    endBuffer[strcspn(endBuffer, "\n")] = '\0';
    gameLog << "=== Game Session Ended: " << endBuffer << " ===\n\n";
    gameLog.close();

    system("pause");
}
