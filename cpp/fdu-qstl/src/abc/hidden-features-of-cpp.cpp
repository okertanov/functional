
http://stackoverflow.com/questions/132241/hidden-features-of-c
http://stackoverflow.com/questions/75538/hidden-features-of-c

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

enum state {
    stopped = 'STOP',
    running = 'RUN!',
    waiting = 'WAIT',
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

FSM {
  STATE(x) {
    ...
    NEXTSTATE(y);
  }

  STATE(y) {
    ...
    if (x == 0)
      NEXTSTATE(y);
    else
      NEXTSTATE(x);
  }
}

// that can be achieved with the following macros:

#define FSM
#define STATE(x)      s_##x :
#define NEXTSTATE(x)  goto s_##x

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <stdio.h>

int main() {
    int a = 3;
    float b = 6.412355;
    printf("%.*f\n",a,b);
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In GCC there is __builtin_trap and for MSVC __debugbreak which will work on any supported architecture.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <stdio.h>

int main() {
    int a;

    printf("1234 %n \n",&a);
    return a;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <stdio.h>
#include <stdlib.h>

int main()
{

   1 || puts("Hello\n");
   0 || puts("Hi\n");
   1 && puts("ROFL\n");
   0 && puts("LOL\n");
   exit( 0 );
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Lambda's (e.g. anonymous functions) in GCC:

#define lambda(return_type, function_body) \
    ({ return_type fn function_body fn })

// This can be used as:
lambda (int, (int x, int y) { return x > y; })(1, 2)

// Which is expanded into:
({ int fn (int x, int y) { return x > y } fn; })(1, 2)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct {
  int    a:3;
  int    b:2;
  int     :0;
  int    c:4;
  int    d:3;
};

// which will give a layout of
// 000aaabb 0ccccddd
// instead of without the :0;
// 0000aaab bccccddd
// The 0 width field tells that the following bitfields should be set on the next atomic entity (char)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define UNUSED(expr) do { (void)(expr); } while (0)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

// see: http://kerneltrap.org/node/4705
// What I like about this is that it also adds some expressiveness to some functions.

void foo(int arg)
{
     if (unlikely(arg == 0)) {
           do_this();
           return;
     }
     do_that();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

(value ? function1 : function2)()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const MyClass& x = MyClass(); // temporary exists as long as x is in scope

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Main usage would be to translate exception to other exception class and rethrow,
// or to translate between exceptions and return-based error code handling.
//
// return is only banned for constructors. A constructor's function try block will catch errors initializing
// the base and members (the only case where a function try block does something different than just having
// a try inside the function); not re-throwing would result in an incomplete object.
//
// this is the only way to handle exceptions thrown by anything in a constructor'sinitialiser list, 
// such as base classes' constructors or those of data.

int Function()
try
{
   return 42;
}
catch(...)
{
   return -1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Many know of the identity / id metafunction, but there is a nice usecase for it for non-template cases:
// Ease writing declarations:

// void (*f)(); // same
id<void()>::type *f;

// void (*f(void(*p)()))(int); // same
id<void(int)>::type *f(id<void()>::type *p);

// int (*p)[2] = new int[10][2]; // same
id<int[2]>::type *p = new int[10][2];

// void (C::*p)(int) = 0; // same
id<void(int)>::type C::*p = 0;

// It helps decrypting C++ declarations greatly!
// boost::identity is pretty much the same

template<typename T>
struct id { typedef T type; };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Sometimes you make valid use of the comma operator,
// but you want to ensure that no user defined comma operator gets into the way,
// because for instance you rely on sequence points between the left and right side or
// want to make sure nothing interferes with the desired action. This is where void() comes into game:

for(T i, j; can_continue(i, j); ++i, void(), ++j)

  do_code(i, j);

// Ignore the place holders i put for the condition and code.
// What's important is the void(),
// which makes the compiler force to use the builtin comma operator.
// This can be useful when implementing traits classes, sometimes, too.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Another hidden feature is that you can call class objects that can be converted to function pointers or references.
// Overload resolution is done on the result of them, and arguments are perfectly forwarded.

template<typename Func1, typename Func2>
class callable {
  Func1 *m_f1;
  Func2 *m_f2;
public:
  callable(Func1 *f1, Func2 *f2):m_f1(f1), m_f2(f2) { }
  operator Func1*() { return m_f1; }
  operator Func2*() { return m_f2; }
};

void foo(int i) { std::cout << "foo: " << i << std::endl; }
void bar(long il) { std::cout << "bar: " << il << std::endl; }

int main() {
  callable<void(int), void(long)> c(foo, bar);
  c(42); // calls foo
  c(42L); // calls bar
}

// These are called "surrogate call functions".

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// void functions can return void values
// Little known, but the following code is fine

void f() { }
void g() { return f(); }

// Aswell as the following weird looking one

void f() { return (void)"i'm discarded"; }

// Knowing about this, you can take advantage in some areas. One example:
// void functions can't return a value but you can also not just return nothing,
// because they may be instantiated with non-void.
// Instead of storing the value into a local variable, which will cause an error for void,
// just return a value directly

template<typename T>
struct sample
{
  // assume f<T> may return void
  T dosomething() { return f<T>(); }
  // better than T t = f<T>(); /* ... */ return t; !
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// You can template bitfields.
template <size_t X, size_t Y>
struct bitfield
{
    char left  : X;
    char right : Y;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

http://www.parashift.com/c++-faq-lite/dtors.html#faq-11.10
// [11.10] What is "placement new" and why would I use it?
// There are many uses of placement new. The simplest use is to place an object at a particular location in memory.
// This is done by supplying the place as a pointer parameter to the new part of a new expression:

#include <new>        // Must #include this to use "placement new"
#include "Fred.h"     // Declaration of class Fred

void someCode()
{
  char memory[sizeof(Fred)];     // Line #1
  void* place = memory;          // Line #2

  Fred* f = new(place) Fred();   // Line #3 (see "DANGER" below)
  // The pointers f and place will be equal

}

// Line #1 creates an array of sizeof(Fred) bytes of memory, which is big enough to hold a Fred object.
// Line #2 creates a pointer place that points to the first byte of this memory (experienced C programmers
// will note that this step was unnecessary; it's there only to make the code more obvious).
// Line #3 essentially just calls the constructor Fred::Fred().
// The this pointer in the Fred constructor will be equal to place. The returned pointer f will therefore be equal to place.

// ADVICE: Don't use this "placement new" syntax unless you have to.
// Use it only when you really care that an object is placed at a particular location in memory.
// For example, when your hardware has a memory-mapped I/O timer device,
// and you want to place a Clock object at that memory location.

// DANGER: You are taking sole responsibility that the pointer you pass to the "placement new" operator
// points to a region of memory that is big enough and is properly aligned for the object type that you're creating.
// Neither the compiler nor the run-time system make any attempt to check whether you did this right.
// If your Fred class needs to be aligned on a 4 byte boundary but you supplied a location that isn't properly aligned,
// you can have a serious disaster on your hands (if you don't know what "alignment" means, please don't use the placement new syntax).
// You have been warned.

// You are also solely responsible for destructing the placed object. This is done by explicitly calling the destructor:

 void someCode()
 {
   char memory[sizeof(Fred)];
   void* p = memory;
   Fred* f = new(p) Fred();
   ...
   f->~Fred();   // Explicitly call the destructor for the placed object
 }

// This is about the only time you ever explicitly call a destructor.
// Note: there is a much cleaner but more sophisticated way of handling the destruction / deletion situation.
// http://www.parashift.com/c++-faq-lite/dtors.html#faq-11.14

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class A { };

struct B
{
  A a;
  operator A&() { return a; }
};

void func(A a) { }

int main()
{
  A a, c;
  B b;
  a=c;
  func(b); //yeah baby
  a=b; //gotta love this
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Getting rid of forward declarations:

struct global
{
     void main()
     {
           a = 1;
           b();
     }
     int a;
     void b(){}
}
singleton;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Normalizing/wrapping angle- and time-values:
int angle = (short)((+180+30)*65536/360) * 360/65536; //==-150

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// The ternary conditional operator ?: requires its second and third operand to have "agreeable" types (speaking informally).
// But this requirement has one exception (pun intended): either the second or third operand can be a throw expression (which has type void),
// regardless of the type of the other operand.
// In other words, one can write the following pefrectly valid C++ expressions using the ?: operator

i = a > b ? a : throw something();

// BTW, the fact that throw expression is actually an expression (of type void) and not a statement is another little-known feature of C++ language.
// This means, among other things, that the following code is perfectly valid

void foo()
{
  return throw something();
}

// although there's not much point in doing it this way (maybe in some generic template code this might come handy).

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct Person
{
  Person() : name("???") { }
  char name[255];
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Unions can also have members and methods, and default to public access similarly to structs.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can view all the predefined macros through command-line switches with some compilers. This works with gcc and icc (Intel's C++ compiler):

$ touch empty.cpp
$ g++ -E -dM empty.cpp | sort >gxx-macros.txt
$ icc -E -dM empty.cpp | sort >icx-macros.txt
$ touch empty.c
$ gcc -E -dM empty.c | sort >gcc-macros.txt
$ icc -E -dM empty.c | sort >icc-macros.txt

// For MSVC they are listed in a single place. They could be documented in a single place for the others too,
// http://msdn.microsoft.com/en-us/library/b0084kay%28VS.80%29.aspx
// but with the above commands you can clearly see what is and isn't defined and exactly what values are used,
// after applying all of the other command-line switches.

// Compare (after sorting):

 $ diff gxx-macros.txt icx-macros.txt
 $ diff gxx-macros.txt gcc-macros.txt
 $ diff icx-macros.txt icc-macros.txt

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

http://en.wikipedia.org/wiki/SFINAE

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Mixins are the right approach, however overloading operator new is not. This will accomplish what you need:

__declspec(align(256))  struct cachealign{};
__declspec(align(4096)) struct pagealign{};

struct DefaultAlign{};
struct CacheAlign:private cachealign{};
struct PageAlign: CacheAlign,private pagealign{};

void foo(){
 DefaultAlign d;
 CacheAlign c;
 PageAlign p;
 std::cout<<"Alignment of d "<<__alignof(d)<<std::endl;
 std::cout<<"Alignment of c "<<__alignof(c)<<std::endl;
 std::cout<<"Alignment of p "<<__alignof(p)<<std::endl;
}

// Prints
// Alignment of d 1
// Alignment of c 256
// Alignment of p 4096

//For gcc, use

struct cachealign{}__attribute__ ((aligned (256)));

// Note that there is automatic selection of the largest alignment, and this works for objects placed on the stack,
// ones that are new'd, and as members of other classes.
// Nor does it add any virtuals and assuming EBCO,
// no extra size to the class (outside of the padding needed for the alignment itself).

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char* argv[])
{
    std::vector<std::string> params(argv, argv+argc);
    // Now all the command-line parameters are in the 'params' vector
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

transform(container.begin(), container.end(), container.begin(),
          bind1st(multiplies<double>(),5.0));

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

s += std::accumulate(s.begin(), s.end(), MD5Hasher());

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const int len = computeLength( inputData );
vector<char> buf( len );
if ( !checkDataForValidity( &convertedData[0] ) )
    return false;
processData( &convertedData[0] );
return true;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CObject *p = (CObject*)malloc(sizeof *p);
...
p = new(p) CObject;
p->DoSomthing();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// The header file looks like this:

#include <memory>

class SomeClass
{
 struct Impl;
 std::auto_ptr<Impl> pimpl;
public:
 SomeClass();
 void someFunction();
};

// The source file:

#include "SomeClass.h"
#include <iostream>

struct SomeClass::Impl
{
 ~Impl()
 {
    std::cout << "destructed";
 }
};

SomeClass::SomeClass()
: pimpl(new Impl())
{}

void SomeClass::someFunction()
{}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// std::vector can be used to create a dynamically sized buffer on the stack.
// Like in this example (which shows how to convert a std::string into a std::wstring)

#include <vector>
#include <locale>
#include <string>
using namespace std;

string narrowStr("narrow");
wstring wideStr;
locale loc("german");

vector<wchar_t> wBuffer( narrowStr.length() );  // = wchar_t[narrowStr.length()]

use_facet<ctype<wchar_t> >(loc)._Widen_s(
    narrowStr.c_str(),
    narrowStr.c_str() + narrowStr.length(),
    &wBuffer[0],
    wBuffer.size()
);
wideStr = wstring( &wBuffer[0], wBuffer.size() );

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

auto int i is equal to int i;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// x.h
export template <class T> struct X {
        void f();
};

// x.c
#include <stdio.h>
#include "x.h"

void g(){
        printf("Hello\n");
}

template <class T> void X<T>::f(){
        g();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typeof(obj).name()
typeid(obj).name()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

http://lucumr.pocoo.org/2010/11/24/collections-in-c/

#define assert(Expr) do { \
    if (!(Expr)) fail_with_message("Assertion failed: " #Expr, \
                                   __LINE__, __FILE__); \
} while (0)

#define _CAT(A, B) A##B
#define CAT(A, B) _CAT(A, B)

int CAT(foo, CAT(bar, baz));

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A::A(const B& b) try : mB(b)
{
    // constructor stuff
}
catch (/* exception type */)
{
    // handle the exception
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

