#include "Stronghold.h"
#include <iostream>
#include <limits>

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int

main() {
    try {
        Kingdom kingdom1("Westoria");
        Kingdom kingdom2("Eastland");
        Communication comm;
        Alliance alliances;
        Trade trade;
        Map gameMap(10, 10);

        gameMap.moveKingdom("Westoria", 2, 2);
        gameMap.moveKingdom("Eastland", 8, 8);

        while (true) {
            cout << "\nStronghold Game Menu:\n";
            cout << "1. Update Kingdoms\n";
            cout << "2. Send Message\n";
            cout << "3. View Messages\n";
            cout << "4. Form Alliance\n";
            cout << "5. Break Alliance\n";
            cout << "6. Create Trade Offer\n";
            cout << "7. Accept Trade Offer\n";
            cout << "8. Save Game\n";
            cout << "9. Load Game\n";
            cout << "10. View Stats\n";
            cout << "11. Exit\n";
            cout << "Enter choice: ";

            int choice;
            cin >> choice;
            clearInputBuffer();

            if (choice == 11) break;

            switch (choice) {
            case 1:
                kingdom1.update();
                kingdom2.update();
                cout << "Kingdoms updated.\n";
                break;
            case 2: {
                string sender, content;
                cout << "Enter sender (Westoria/Eastland): ";
                getline(cin, sender);
                cout << "Enter message: ";
                getline(cin, content);
                comm.sendMessage(sender, content);
                comm.saveChatLog("chat_log.txt");
                cout << "Message sent.\n";
                break;
            }
            case 3: {
                int count;
                string* messages = comm.getMessages(count);
                for (int i = 0; i < count; i++) {
                    cout << messages[i] << "\n";
                }
                delete[] messages;
                break;
            }
            case 4:
                alliances.formAlliance("Westoria", "Eastland");
                cout << "Alliance formed between Westoria and Eastland.\n";
                break;
            case 5:
                alliances.breakAlliance("Westoria", "Eastland");
                cout << "Alliance broken between Westoria and Eastland.\n";
                break;
            case 6: {
                string from, to, resource;
                double amount, price;
                cout << "Enter from kingdom: ";
                getline(cin, from);
                cout << "Enter to kingdom: ";
                getline(cin, to);
                cout << "Enter resource: ";
                getline(cin, resource);
                cout << "Enter amount: ";
                cin >> amount;
                cout << "Enter price: ";
                cin >> price;
                clearInputBuffer();
                trade.createOffer(from, to, resource, amount, price);
                cout << "Trade offer created.\n";
                break;
            }
            case 7: {
                string kingdom, offerId;
                cout << "Enter kingdom: ";
                getline(cin, kingdom);
                cout << "Enter offer ID: ";
                getline(cin, offerId);
                Kingdom& target = (kingdom == "Westoria") ? kingdom1 : kingdom2;
                if (trade.acceptOffer(kingdom, offerId, target.getResources())) {
                    cout << "Trade offer accepted.\n";
                }
                else {
                    cout << "Trade offer failed.\n";
                }
                break;
            }
            case 8:
                kingdom1.saveGame("game_save.txt");
                kingdom2.saveGame("game_save.txt");
                cout << "Game saved.\n";
                break;
            case 9:
                kingdom1.loadGame("game_save.txt");
                kingdom2.loadGame("game_save.txt");
                cout << "Game loaded.\n";
                break;
            case 10:
                kingdom1.logStats("score.txt");
                kingdom2.logStats("score.txt");
                cout << "Stats logged to score.txt.\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
        }

    }
    catch (const CustomException& e) {
        cerr << "Error: " << e.message << endl;
        return 1;
    }

    return 0;
}
