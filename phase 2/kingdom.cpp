#include "Kingdom.hpp"

Kingdom::Kingdom(std::string n, int pop, int morale, int army)
    : name(n), population(pop), morale(morale), armyStrength(army), resourceCount(0), policyCount(0) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        resources[i] = nullptr;
    }
    for (int i = 0; i < MAX_POLICIES; ++i) {
        policies[i].active = false;
    }
    applyPolicy("tax_rate", 10);
    applyPolicy("conscription", 5);
}

Kingdom::~Kingdom() {
    for (int i = 0; i < resourceCount; ++i) {
        delete resources[i];
    }
}

bool Kingdom::addResource(Resource* r) {
    if (resourceCount >= MAX_RESOURCES) {
        std::cout << "Cannot add resource: Maximum limit reached!" << std::endl;
        return false;
    }
    resources[resourceCount++] = r;
    return true;
}

Resource* Kingdom::getResource(std::string name) {
    for (int i = 0; i < resourceCount; ++i) {
        if (resources[i]->getName() == name) {
            return resources[i];
        }
    }
    return nullptr;
}

void Kingdom::updateEconomy() {
    int taxRate = 0;
    for (int i = 0; i < policyCount; ++i) {
        if (policies[i].active && policies[i].name == "tax_rate") {
            taxRate = policies[i].value;
            break;
        }
    }
    int taxIncome = population * taxRate / 100;
    Resource* gold = getResource("Gold");
    if (gold) gold->modifyQuantity(taxIncome);
    morale -= taxRate / 5;
    if (morale < 0) morale = 0;
}

void Kingdom::updatePopulation() {
    Resource* food = getResource("Food");
    int foodSupply = food ? food->getQuantity() : 0;
    if (foodSupply >= population) {
        population += population / 20;
        if (food) food->modifyQuantity(-population);
    }
    else {
        population -= (population - foodSupply) / 10;
        morale -= 10;
    }
    if (morale < 0) morale = 0;
    if (population < 0) population = 0;
}

void Kingdom::updateArmy() {
    int conscription = 0;
    for (int i = 0; i < policyCount; ++i) {
        if (policies[i].active && policies[i].name == "conscription") {
            conscription = policies[i].value;
            break;
        }
    }
    int newRecruits = population * conscription / 100;
    armyStrength += newRecruits;
    population -= newRecruits;
    morale -= conscription / 2;
    if (morale < 0) morale = 0;
}

bool Kingdom::applyPolicy(std::string policy, int value) {
    if (policy == "population") {
        population = value;
        if (population < 0) population = 0;
        return true;
    }
    else if (policy == "morale") {
        morale = value;
        if (morale < 0) morale = 0;
        return true;
    }
    else if (policy == "armyStrength") {
        armyStrength = value;
        if (armyStrength < 0) armyStrength = 0;
        return true;
    }
    else {
        for (int i = 0; i < policyCount; ++i) {
            if (policies[i].active && policies[i].name == policy) {
                policies[i].value = value;
                return true;
            }
        }
        if (policyCount >= MAX_POLICIES) {
            std::cout << "Cannot add policy: Maximum limit reached!" << std::endl;
            return false;
        }
        policies[policyCount] = { policy, value, true };
        policyCount++;
        return true;
    }
}

void Kingdom::display() const {
    std::cout << "Kingdom: " << name << std::endl;
    std::cout << "Population: " << population << std::endl;
    std::cout << "Morale: " << morale << std::endl;
    std::cout << "Army Strength: " << armyStrength << std::endl;
    std::cout << "Resources:" << std::endl;
    for (int i = 0; i < resourceCount; ++i) {
        resources[i]->display();
    }
    std::cout << "Policies:" << std::endl;
    for (int i = 0; i < policyCount; ++i) {
        if (policies[i].active) {
            std::cout << policies[i].name << ": " << policies[i].value << std::endl;
        }
    }
}