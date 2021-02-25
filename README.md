![privablic logo](https://raw.githubusercontent.com/altamic/privablic/master/images/privablic.png)

Access to private members and methods in C++

## How to use it

Copy [privablic.h](https://raw.githubusercontent.com/altamic/privablic/master/privablic.h) into your project and `#include "privablic.h"`, and for easy reading, add: 
```cpp
using namespace privablic;
```
Now, suppose you know the implementation of a class (or a struct) like that:

```cpp
class Sheep 
{
public:
    Sheep(string name_) : name{ std::move(name_) } {}
    
private:
    // Data
    string name;
    static int TOTAL;

    // Functions
    void baa() { std::cout << name << ": Baa! Baa!\n"; };
    
    static void FlockCount() 
    {
      std::cout << "sheperd actually counted " << TOTAL << " sheep\n";
    }
};

int Sheep::TOTAL = 42;
```
You only have to map some stubs according to types of members and/or methods signatures:

### Instance Member
```cpp
struct Sheep_name { typedef string (Sheep::*type); };
template class private_member<Sheep_name, &Sheep::name>;
```

### Instance Method
```cpp
struct Sheep_baa { typedef void(Sheep::*type)(); };
template class private_method<Sheep_baa, &Sheep::baa>;
```

### Static Instance Member
```cpp
struct Sheep_TOTAL { typedef int *type; };
template class private_member<Sheep_TOTAL, &Sheep::TOTAL>;
```

### Static Instance Method
```cpp
struct Sheep_FlockCount { typedef void(*type)(); };
template class private_method<Sheep_FlockCount, &Sheep::FlockCount>;
```

Then, using an instance of `Sheep`, you can access the private members like this:
```cpp
Sheep dolly = Sheep("Dolly");

// now we have a sheep under our complete control:

// - change dolly's identity
dolly.*member<Sheep_name>::value = "Lilly";

// - make dolly baa
(&dolly->*func<Sheep_baa>::ptr)();

// - steal dolly
int flockCount = *member<Sheep_TOTAL>::value -= 1;

// - let the sheperd realize it
(*func<Sheep_FlockCount>::ptr)();
```

#### Output:

```
Lilly: Baa! Baa!
sheperd actually counted 41 sheeps
```

# Tested compilers which works with

## clang

Works under OSX

## gcc

GCC 7.x (at least!)

## msvc

Visual Studio 2019 (at least!)


# Credits

* [Johannes Schaub (litb)](http://bloglitb.blogspot.com/2010/07/access-to-private-members-thats-easy.html)
* [Dave Abrahams](https://gist.github.com/dabrahams/1528856)
* [Christof Warlich](http://bloglitb.blogspot.it/2010/07/access-to-private-members-thats-easy.html?showComment=1461746009339#c7258461447914486699)


# License

Copyright 2017 Michelangelo Altamore. It may be redistributed under the terms specified in the [LICENSE](LICENSE) file.

