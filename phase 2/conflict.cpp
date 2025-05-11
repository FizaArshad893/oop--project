#include "Conflict.hpp"
#include <cstdlib>

void Conflict::attack(Kingdom* attacker, Kingdom* defender, Alliance* alliances) {
    int attackPower = attacker->getArmyStrength();
    int defensePower = defender->getArmyStrength();
    bool attackerWins = (rand() % (attackPower + defensePower)) < attackPower;

    if (alliances->isAllied(attacker->getName(), defender->getName())) {
        alliances->breakTreaty(attacker->getName(), defender->getName());
        attacker->applyPolicy("morale", attacker->getMorale() - 20);
        std::cout << attacker->getName() << " betrayed " << defender->getName() << "!" << std::endl;
    }

    if (attackerWins) {
        defender->applyPolicy("population", defender->getPopulation() - 100);
        defender->applyPolicy("morale", defender->getMorale() - 15);
        attacker->addResource(new Gold(50));
        std::cout << attacker->getName() << " defeated " << defender->getName() << "!" << std::endl;
    }
    else {
        attacker->applyPolicy("armyStrength", attacker->getArmyStrength() - 50);
        attacker->applyPolicy("morale", attacker->getMorale() - 10);
        std::cout << defender->getName() << " repelled " << attacker->getName() << "!" << std::endl;
    }
}

void Conflict::surpriseAttack(Kingdom* attacker, Kingdom* defender, Alliance* alliances) {
    int attackPower = attacker->getArmyStrength() * 1.5;
    int defensePower = defender->getArmyStrength();
    bool attackerWins = (rand() % (attackPower + defensePower)) < attackPower;

    if (alliances->isAllied(attacker->getName(), defender->getName())) {
        alliances->breakTreaty(attacker->getName(), defender->getName());
        attacker->applyPolicy("morale", attacker->getMorale() - 30);
        std::cout << attacker->getName() << " betrayed " << defender->getName() << " with a surprise attack!" << std::endl;
    }

    if (attackerWins) {
        defender->applyPolicy("population", defender->getPopulation() - 150);
        defender->applyPolicy("morale", defender->getMorale() - 20);
        attacker->addResource(new Gold(100));
        std::cout << attacker->getName() << " crushed " << defender->getName() << "!" << std::endl;
    }
    else {
        attacker->applyPolicy("armyStrength", attacker->getArmyStrength() - 100);
        attacker->applyPolicy("morale", attacker->getMorale() - 15);
        std::cout << defender->getName() << " repelled " << attacker->getName() << "'s surprise attack!" << std::endl;
    }
}