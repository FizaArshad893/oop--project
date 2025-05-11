#include "Communication.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>  // For strcspn

Communication::Communication() {
    chatLog.open("logs/chat_log.txt", std::ios::app);
}

Communication::~Communication() {
    if (chatLog.is_open()) chatLog.close();
}

void Communication::sendMessage(const std::string& sender, const std::string& receiver, const std::string& message) {
    time_t now = time(nullptr);

    // Secure timestamp generation
    char timestamp[100];
    ctime_s(timestamp, sizeof(timestamp), &now);
    timestamp[strcspn(timestamp, "\n")] = '\0';  // Remove newline character

    chatLog << "[" << timestamp << "] " << sender << " to " << receiver << ": " << message << std::endl;
    std::cout << sender << " sent to " << receiver << ": " << message << std::endl;
}

void Communication::displayMessages() const {
    std::ifstream inLog("logs/chat_log.txt");
    std::string line;
    while (std::getline(inLog, line)) {
        std::cout << line << std::endl;
    }
    inLog.close();
}
