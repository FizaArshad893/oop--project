#include "Alliance.hpp"
#include <iostream>
#include <ctime>

Alliance::Alliance() : treatyCount(0) {
    treatyLog.open("logs/treaty_log.txt", std::ios::app);
    for (int i = 0; i < MAX_TREATIES; ++i) {
        treaties[i].active = false;
    }
}

Alliance::~Alliance() {
    if (treatyLog.is_open()) treatyLog.close();
}

bool Alliance::formTreaty(const std::string& k1, const std::string& k2, const std::string& type, int duration) {
    if (treatyCount >= MAX_TREATIES) {
        std::cout << "Cannot form treaty: Maximum limit reached!" << std::endl;
        return false;
    }

    treaties[treatyCount] = { k1, k2, type, duration, true };
    treatyCount++;

    time_t now = time(nullptr);
    char buffer[100];
    ctime_s(buffer, sizeof(buffer), &now);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove newline

    treatyLog << "[" << buffer << "] Treaty formed: " << k1 << " and " << k2 << " (" << type << ", " << duration << " turns)" << std::endl;
    std::cout << "Treaty formed between " << k1 << " and " << k2 << std::endl;
    return true;
}

void Alliance::breakTreaty(const std::string& k1, const std::string& k2) {
    for (int i = 0; i < treatyCount; ++i) {
        if (treaties[i].active && ((treaties[i].kingdom1 == k1 && treaties[i].kingdom2 == k2) ||
            (treaties[i].kingdom1 == k2 && treaties[i].kingdom2 == k1))) {

            treaties[i].active = false;
            time_t now = time(nullptr);
            char buffer[100];
            ctime_s(buffer, sizeof(buffer), &now);
            buffer[strcspn(buffer, "\n")] = '\0';

            treatyLog << "[" << buffer << "] Treaty broken: " << k1 << " and " << k2 << std::endl;
            std::cout << "Treaty broken between " << k1 << " and " << k2 << std::endl;
            return;
        }
    }
}

bool Alliance::isAllied(const std::string& k1, const std::string& k2) const {
    for (int i = 0; i < treatyCount; ++i) {
        if (treaties[i].active && ((treaties[i].kingdom1 == k1 && treaties[i].kingdom2 == k2) ||
            (treaties[i].kingdom1 == k2 && treaties[i].kingdom2 == k1))) {
            return true;
        }
    }
    return false;
}

void Alliance::updateTreaties() {
    for (int i = 0; i < treatyCount; ++i) {
        if (treaties[i].active) {
            treaties[i].duration--;
            if (treaties[i].duration <= 0) {
                treaties[i].active = false;

                time_t now = time(nullptr);
                char buffer[100];
                ctime_s(buffer, sizeof(buffer), &now);
                buffer[strcspn(buffer, "\n")] = '\0';

                treatyLog << "[" << buffer << "] Treaty expired: " << treaties[i].kingdom1
                    << " and " << treaties[i].kingdom2 << std::endl;
            }
        }
    }
}

void Alliance::displayTreaties() const {
    std::cout << "Active Treaties:" << std::endl;
    for (int i = 0; i < treatyCount; ++i) {
        if (treaties[i].active) {
            std::cout << treaties[i].kingdom1 << " and " << treaties[i].kingdom2
                << " (" << treaties[i].type << ", " << treaties[i].duration << " turns)" << std::endl;
        }
    }
}
