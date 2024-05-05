#ifndef CPP_DYNAMIC_POLYMORPHISM_H
#define CPP_DYNAMIC_POLYMORPHISM_H


class dynamic_polymorphism {
protected:
    int x = 0;
public:

    virtual void increment();
    void decrement();

};

class Derived : public dynamic_polymorphism {
public:
    void increment() override;
};

#endif //CPP_DYNAMIC_POLYMORPHISM_H
