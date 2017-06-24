#include "sheep.h"

Sheep::Sheep(string name) { name = name; };

int Sheep::TOTAL = 42;

void Sheep::FlockCount() { 
  cout << "sheperd actually counted " << 
    TOTAL << " sheeps" << endl;
};

extern "C" Sheep * obtain(const char * name) {
    return new Sheep(name);
}

