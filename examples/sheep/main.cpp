#include "Sheep.cpp" // include the impl in order to resolve symbols
#include <dlfcn.h>
#include "privablic.h"

const char * libName = "libSheep.so";
const char * obtain_sym  = "obtain";

//  Privablic mappings to:

// instance member
struct Sheep_name { typedef string (Sheep::*type); };
template class private_member<Sheep_name, &Sheep::name>;

// instance method
struct Sheep_baa { typedef void(Sheep::*type)(); };
template class private_method<Sheep_baa, &Sheep::baa>;

// static instance member
struct Sheep_TOTAL { typedef int *type; };
template class private_member<Sheep_TOTAL, &Sheep::TOTAL>;

// static instance method
struct Sheep_FlockCount { typedef void(*type)(); };
template class private_method<Sheep_FlockCount, &Sheep::FlockCount>;


int main()
{
  void * libHandle = dlopen(libName, RTLD_NOW);
  if (libHandle == NULL) {
    printf("Cannot load library '%s'\n", libName);
    exit(EXIT_FAILURE);
  }

  // acquire a sheep at runtime
  obtain_sheep_t * obtain_sheep =
    (obtain_sheep_t*) dlsym(libHandle, obtain_sym);
  if (dlerror()) {
    printf("Cannot load symbol '%s'\n", obtain_sym);
    exit(EXIT_FAILURE);
  }

  Sheep * dolly = obtain_sheep("Dolly");

  // - change dolly's identity
  (*dolly).*member<Sheep_name>::value = "Lilly";

  // - make dolly baa
  (dolly->*func<Sheep_baa>::ptr)();

  // - steal dolly
  int flockCount = *member<Sheep_TOTAL>::value -= 1;

  // - let the sheperd realize it
  (*func<Sheep_FlockCount>::ptr)();
 
  dlclose(libHandle);

  exit(EXIT_SUCCESS);
}

/*

OUTPUT:
  $ ./main
  Lilly: Baa! Baa!
  sheperd actually counted 41 sheeps

*/

