template <class T>
class A {};

class B: public A<int> {
    public:
        // Good.
        B(): A(){}

        // Also fine.
        // B(): A<int>(){}
};

int main(){}