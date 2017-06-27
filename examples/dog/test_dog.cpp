#include "privablic.h"
#include "dog.hpp"

struct Dog_name { typedef string (Dog::*type); };
template class private_member<Dog_name, &Dog::name>;

struct Dog_bark { typedef string (Dog::*type)(); };
template class private_method<Dog_bark, &Dog::bark>;

struct Dog_Species { typedef string *type; };
template class private_member<Dog_Species, &Dog::Species>;

struct Dog_Legs { typedef int (*type)(); };
template class private_method<Dog_Legs, &Dog::Legs>;

#include <assert.h>

int main()
{
    string name = "Fido";
    Dog fido = Dog(name);

    string fido_name = fido.*member<Dog_name>::value;
    assert (fido_name == name);

    string fido_bark = (&fido->*func<Dog_bark>::ptr)();
    string bark = "Fido: Woof!";
    assert( fido_bark == bark);

    string fido_species = *member<Dog_Species>::value;
    string species = "Canis familiaris";
    assert(fido_species == species);

    int fido_legs = (*func<Dog_Legs>::ptr)();
    int legs = 4;
    assert(fido_legs == legs);

    printf("all assertions passed\n");
};

