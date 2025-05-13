#include "Stronghold.h"

Communication::Communication() : messageCount(0), messageCapacity(100) {
    messages = new Message[messageCapacity];
}

Communication::~Communication() {
    delete[] messages;
}

void Communication::sendMessage(const string& sender, const string& content) {
    if (sender.empty() || content.empty())
        throw CustomException("Empty message or sender");
    if (messageCount >= messageCapacity)
        throw CustomException("Message capacity exceeded");
    messages[messageCount].sender = sender;
    messages[messageCount].content = content;
    messageCount++;
}

string* Communication::getMessages(int& count) const {
    count = messageCount;
    string* result = new string[messageCount];
    for (int i = 0; i < messageCount; i++) {
        result[i] = messages[i].sender + ": " + messages[i].content;
    }
    return result;
}

void Communication::saveChatLog(const string& filename) const {
    ofstream out(filename, ios::app);
    if (!out) throw CustomException("Failed to open chat log");
    for (int i = 0; i < messageCount; i++) {
        out << messages[i].sender << ": " << messages[i].content << "\n";
    }
}
