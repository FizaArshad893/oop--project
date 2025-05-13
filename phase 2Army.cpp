#include "Stronghold.h"

Army::Army() : size(100), morale(0.7), trainingLevel(0.5) {}

void Army::recruit(int num, const Population& pop) {
    if (num < 0 || num > pop.getCount() / 2)
        throw CustomException("Invalid recruitment number");
    size += num;
    morale = max(0.0, morale - 0.1);
}

void Army::train(double resources) {
    if (resources < 0)
        throw CustomException("Negative resources");
    trainingLevel = min(1.0, trainingLevel + resources * 0.01);
    morale = min(1.0, morale + 0.05);
}

void Army::saveState(ofstream& out) const {
    out << size << " " << morale << " " << trainingLevel << "\n";
}

void Army::loadState(ifstream& in) {
    in >> size >> morale >> trainingLevel;
}
