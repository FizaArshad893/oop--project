#include "Stronghold.h"

Bank::Bank() : treasury(10000.0), corruptionLevel(0.1) {}

void Bank::processLoan(double amount, double interest) {
    if (amount <= 0 || interest < 0)
        throw CustomException("Invalid loan parameters");
    treasury += amount;
    treasury -= amount * interest * corruptionLevel;
}

void Bank::audit() {
    corruptionLevel = max(0.0, corruptionLevel - 0.05);
    treasury *= (1.0 - corruptionLevel);
}

void Bank::saveState(ofstream& out) const {
    out << treasury << " " << corruptionLevel << "\n";
}

void Bank::loadState(ifstream& in) {
    in >> treasury >> corruptionLevel;
}
