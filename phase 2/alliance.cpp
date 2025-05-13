#include "Stronghold.h"

Alliance::Alliance() : allianceCount(0), allianceCapacity(10) {
    alliances = new AllianceEntry[allianceCapacity];
    for (int i = 0; i < allianceCapacity; i++) {
        alliances[i].allyCount = 0;
        alliances[i].allyCapacity = 10;
        alliances[i].allies = new string[10];
    }
}

Alliance::~Alliance() {
    for (int i = 0; i < allianceCount; i++) {
        delete[] alliances[i].allies;
    }
    delete[] alliances;
}

void Alliance::formAlliance(const string& kingdom1, const string& kingdom2) {
    if (kingdom1 == kingdom2)
        throw CustomException("Cannot ally with self");
    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < allianceCount; i++) {
        if (alliances[i].kingdom == kingdom1) idx1 = i;
        if (alliances[i].kingdom == kingdom2) idx2 = i;
    }
    if (idx1 == -1) {
        if (allianceCount >= allianceCapacity) throw CustomException("Alliance capacity exceeded");
        idx1 = allianceCount++;
        alliances[idx1].kingdom = kingdom1;
    }
    if (idx2 == -1) {
        if (allianceCount >= allianceCapacity) throw CustomException("Alliance capacity exceeded");
        idx2 = allianceCount++;
        alliances[idx2].kingdom = kingdom2;
    }
    if (alliances[idx1].allyCount >= alliances[idx1].allyCapacity ||
        alliances[idx2].allyCount >= alliances[idx2].allyCapacity)
        throw CustomException("Ally capacity exceeded");
    alliances[idx1].allies[alliances[idx1].allyCount++] = kingdom2;
    alliances[idx2].allies[alliances[idx2].allyCount++] = kingdom1;
}

void Alliance::breakAlliance(const string& kingdom1, const string& kingdom2) {
    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < allianceCount; i++) {
        if (alliances[i].kingdom == kingdom1) idx1 = i;
        if (alliances[i].kingdom == kingdom2) idx2 = i;
    }
    if (idx1 == -1 || idx2 == -1) return;
    for (int i = 0; i < alliances[idx1].allyCount; i++) {
        if (alliances[idx1].allies[i] == kingdom2) {
            alliances[idx1].allies[i] = alliances[idx1].allies[--alliances[idx1].allyCount];
            break;
        }
    }
    for (int i = 0; i < alliances[idx2].allyCount; i++) {
        if (alliances[idx2].allies[i] == kingdom1) {
            alliances[idx2].allies[i] = alliances[idx2].allies[--alliances[idx2].allyCount];
            break;
        }
    }
}

bool Alliance::isAllied(const string& kingdom1, const string& kingdom2) const {
    int idx1 = -1;
    for (int i = 0; i < allianceCount; i++) {
        if (alliances[i].kingdom == kingdom1) {
            idx1 = i;
            break;
        }
    }
    if (idx1 == -1) return false;
    for (int i = 0; i < alliances[idx1].allyCount; i++) {
        if (alliances[idx1].allies[i] == kingdom2) return true;
    }
    return false;
}
