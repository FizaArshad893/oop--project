#ifndef KINGDOM_HPP
#define KINGDOM_HPP

#include "Resource.hpp"
#include <string>

class Kingdom {
private:
    static const int MAX_RESOURCES = 10;
    static const int MAX_POLICIES = 10;
    struct Policy {
        std::string name;
        int value;
        bool active;
    };
    std::string name;
    int population;
    int morale;
    int armyStrength;
    Resource* resources[MAX_RESOURCES];
    int resourceCount;
    Policy policies[MAX_POLICIES];
    int policyCount;
public:
    Kingdom(std::string n, int pop, int morale, int army);
    ~Kingdom();
    std::string getName() const { return name; }
    int getPopulation() const { return population; }
    int getMorale() const { return morale; }
    int getArmyStrength() const { return armyStrength; }
    bool addResource(Resource* r);
    Resource* getResource(std::string name);
    void updateEconomy();
    void updatePopulation();
    void updateArmy();
    bool applyPolicy(std::string policy, int value);
    void display() const;
};

#endif 