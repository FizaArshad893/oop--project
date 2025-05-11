#ifndef CONFLICT_HPP
#define CONFLICT_HPP

#include "Kingdom.hpp"
#include "Alliance.hpp"
#include <string>

class Conflict {
public:
    void attack(Kingdom* attacker, Kingdom* defender, Alliance* alliances);
    void surpriseAttack(Kingdom* attacker, Kingdom* defender, Alliance* alliances);
};

#endif 