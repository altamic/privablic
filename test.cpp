#include <iostream>
#include "privablic.h"

// Demonstration
struct A
{
  A() : x("struct private instance member has been accessed") {}
  private:
  char const* x;
  static char const* y;
  void f() {
    std::cout << "struct private instance method has been accessed" << std::endl;
  }
  static void g() {
    std::cout << "struct private static method has been accessed" << std::endl;
  }
};

char const* A::y = "struct private static member has been accessed"; // static member init

// A stub type for A::x.  Each distinct private member you need to
// access should have its own stub.  Each stub should contain a
// nested ::type that is the corresponding pointer-to-member type.
struct A_x { typedef char const*(A::*type); };

// Explicit instantiation; the only place where it is legal to pass
// the address of a private member.  Generates the static ::instance
// that in turn initializes stowed<Stub>::value.
template class private_member<A_x, &A::x>;

// This technique can also be used to access private static member variables.
struct A_y { typedef char const** type; };
template class private_member<A_y, &A::y>;

// This technique can also be used to access private instance methods
struct Af { typedef void(A::*type)(); };
template class private_method<Af, &A::f>;

// and to access private static methods.
struct Ag { typedef void(*type)(); };
template class private_method<Ag, &A::g>;


// with a class
class B {
  public:
    B() { x = 42; }
  private:
    int x;
    static int y;
    void f() { printf("class private instance method: %d\n", x); }
    static void g() { printf("class private static method: %d\n", y ); }
};

int B::y = 42; // initialize static member


struct B_x { typedef int (B::*type); };
template class private_member<B_x, &B::x>;

struct B_y { typedef int *type; };
template class private_member<B_y, &B::y>;

struct Bf { typedef void(B::*type)(); };
template class private_method<Bf, &B::f>;

struct Bg { typedef void(*type)(); };
template class private_method<Bg, &B::g>;

int main()
{
  A a;

  // Use the stowed private member pointer
  std::cout << a.*stowed<A_x>::value << std::endl;

  // Use the stowed private static member pointer
  std::cout << *stowed<A_y>::value << std::endl;

  // Use the stowed private method member pointer
  (a.*result<Af>::ptr)();

  // Use the stowed private static method member pointer
  (*result<Ag>::ptr)();


  B b = B();

  // Use the stowed private member pointer
  printf("class private instance member: %d\n", b.*stowed<B_x>::value);

  // Use the stowed private static member pointer
 printf("class private static member: %d\n", *stowed<B_y>::value);

  // Use the stowed private method member pointer
  (b.*result<Bf>::ptr)();

  // Use the stowed private static method member pointer
  (*result<Bg>::ptr)();

};

/*

   $ clang++ private_access.cpp -o private_access
   $ ./private_access
   struct private instance member has been accessed
   struct private static member has been accessed
   struct private instance method has been accessed
   struct private static method has been accessed
   class private instance member: 42
   class private static member: 42
   class private instance method: 42
   class private static method: 42

*/
