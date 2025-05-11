#ifndef ALLIANCE_HPP
#define ALLIANCE_HPP

#include <string>
#include <fstream>

class Alliance {
private:
    static const int MAX_TREATIES = 20;
    struct Treaty {
        std::string kingdom1;
        std::string kingdom2;
        std::string type;
        int duration;
        bool active;
    };
    Treaty treaties[MAX_TREATIES];
    int treatyCount;
    std::ofstream treatyLog;
public:
    Alliance();
    ~Alliance();
    bool formTreaty(const std::string& k1, const std::string& k2, const std::string& type, int duration);
    void breakTreaty(const std::string& k1, const std::string& k2);
    bool isAllied(const std::string& k1, const std::string& k2) const;
    void updateTreaties();
    void displayTreaties() const;
};

#endif 