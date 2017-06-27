#include "sheep.h"

using namespace std;

Sheep::Sheep(string name) { this->name = name; };

void Sheep::baa() { cout << name << ": Baa! Baa!" << endl; };

int Sheep::TOTAL = 42;

void Sheep::FlockCount() { 
  cout << "sheperd actually counted " << 
    TOTAL << " sheeps" << endl;
};

extern "C" Sheep * obtain(const char * name) {
    return new Sheep(name);
}

