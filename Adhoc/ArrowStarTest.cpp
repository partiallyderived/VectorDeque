#include <iostream>

using namespace std;

class A {
    public:
        int* a;
};

class B {
    public:
        A* aPtr;

        A* operator *() {
            return aPtr;
        }

        A* operator ->() {
            return aPtr;
        }

        template <class C, class D>
        C& operator ->*(D mem) {
            return aPtr->*mem;
        }
};

int main() {
    B b;
    A aa;
    int var = 3;
    aa.a = &var;
    b.aPtr = &aa;
    cout << (*(b->a)) << endl;
}