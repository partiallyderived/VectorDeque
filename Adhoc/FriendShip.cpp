template <class T>
class A {
    int a;
    // Need template argument.
    template <class T2>
    friend void b(T2 t);

};

// No scope operator for definition of b.
// Need template argument.
template <class T>
void b(T t) {
    A<T> a;
    a.a = 3;
}

int main() {

}