#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>
#include <iostream>

class Resource {
protected:
    std::string name;
    int quantity;
public:
    Resource(std::string n, int q) : name(n), quantity(q) {}
    virtual ~Resource() {}
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    void modifyQuantity(int delta) { quantity += delta; if (quantity < 0) quantity = 0; }
    virtual void display() const {
        std::cout << name << ": " << quantity << std::endl;
    }
};

class Food : public Resource {
public:
    Food(int q) : Resource("Food", q) {}
};

class Gold : public Resource {
public:
    Gold(int q) : Resource("Gold", q) {}
};

#endif 