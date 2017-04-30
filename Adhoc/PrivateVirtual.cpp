class A {
    private:
        virtual void doThing() = 0;
};

class B: public A {
    private:
        virtual void doThing(){}
    public:
        void otherThing() {
            doThing();
        }
};

int main() {
    B b;
    b.otherThing();
}