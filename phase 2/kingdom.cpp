#include "Stronghold.h"

Kingdom::Kingdom(const string& n) : name(n), leader(new DemocraticLeader("King Arthur")) {
    resources.addResource("food", 1000.0);
    resources.addResource("wood", 500.0);
    resources.addResource("stone", 300.0);
    resources.addResource("gold", 5000.0);
}

Kingdom::~Kingdom() {
    delete leader;
}

void Kingdom::update() {
    try {
        resources.consumeResource("food", population.getCount() * 0.1);
        army.train(resources.getResource("wood") * 0.1);
        population.updatePopulation(resources.getResource("food") / population.getCount(), bank.getTreasury() / 10000.0);
        bank.audit();
    }
    catch (const CustomException& e) {
        ofstream log("error_log.txt", ios::app);
        log << "Error in update: " << e.message << "\n";
    }
}

void Kingdom::saveGame(const string& filename) const {
    ofstream out(filename, ios::app);
    if (!out) throw CustomException("Failed to open save file");
    out << name << "\n";
    population.saveState(out);
    army.saveState(out);
    bank.saveState(out);
}

void Kingdom::loadGame(const string& filename) {
    ifstream in(filename);
    if (!in) throw CustomException("Failed to open save file");
    getline(in, name);
    population.loadState(in);
    army.loadState(in);
    bank.loadState(in);
}

void Kingdom::logStats(const string& filename) const {
    ofstream out(filename, ios::app);
    if (!out) throw CustomException("Failed to open score file");
    out << "Kingdom: " << name << "\n";
    out << "Population: " << population.getCount() << "\n";
    out << "Army Strength: " << army.getStrength() << "\n";
    out << "Treasury: " << bank.getTreasury() << "\n\n";
}
