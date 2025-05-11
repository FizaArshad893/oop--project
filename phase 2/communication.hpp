#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include <string>
#include <fstream>

class Communication {
private:
    std::ofstream chatLog;
public:
    Communication();
    ~Communication();
    void sendMessage(const std::string& sender, const std::string& receiver, const std::string& message);
    void displayMessages() const;
};

#endif 