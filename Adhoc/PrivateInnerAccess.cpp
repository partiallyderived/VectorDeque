class A {
    private:
        class B {
            private:
                int a;

        };

        void func1() {
            B b;
            b.a = 3;
        }

        class C: public B {};

        void func2() {
            C c;
            c.a = 3;
        }
};

int main() {}