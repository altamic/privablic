#include <iostream>
#include <string>

using namespace std;

class Dog {
  public:
    Dog(string name) { this->name = name; };

  private:
    string name;
    string bark() { return name + ": Woof!"; };
    static string Species;
    static int Legs() { return 4; };
};

string Dog::Species = "Canis familiaris";


