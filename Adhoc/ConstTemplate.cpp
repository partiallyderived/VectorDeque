template <class T>
class A {
    public:
        T* a;
        void thing(A<const int> other) {
            a = other.a;
        }
};

void func(A<const int> a) {

}

int main() {
    A<int> a1;
    A<const int> a2;
    A<const int> a3;
    const int b1 = 3;
    int b2 = 4;
    a1.a = &b2;
    a2.a = &b2;
    a2.a = &b1;
    func(a2);
    a2.thing(a3);
}