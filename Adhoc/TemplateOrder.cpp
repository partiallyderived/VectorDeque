#include <iostream>

using namespace std;

int count = 3;
class A {
    public:
        void a() {
            cout << "a" << endl;
            --count;
            b();
        }

        void b() {
            cout << "b" << endl;
            a();
        }
};

int main() {
    A a;
    a.b();
    a.a();
    a.b();
}