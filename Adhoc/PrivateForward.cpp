class A {
    public:
        class B;
    /* Not allowed to redeclare with different access.
    private:
        class B;
    */
    public:
        class B {

        };
};

int main() {}