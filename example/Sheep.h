#ifndef SHEEP_H
#define SHEEP_H

#include <iostream>
#include <string>

using namespace std;

class Sheep {
  public:
    Sheep(string name);
  private:
    string name;
    void baa() { cout << name << ": Baa! Baa!" << endl; };
    static int TOTAL;
    static void FlockCount();
};

typedef Sheep * obtain_sheep_t(const char *);

#endif

