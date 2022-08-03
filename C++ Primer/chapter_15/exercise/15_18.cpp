#include <iostream>

using namespace std;

class Base {
public:
    void pub_mem();
protected:
    int prot_mem;
    void memfcn(Base &b) { b = *this; }
private:
    char priv_mem;
};

struct Pub_Derv : public Base {
    int f() {return prot_mem; }
    //char g() {return priv_mem; } //错误
    void memfcn(Base &b) { b = *this; }
};

struct Priv_Derv : private Base {
    //private不影响派生类的访问权限
    int f1() const {return prot_mem; }
    void memfcn(Base &b) { b = *this; }
};

struct Prot_Derv : protected Base {
    int f2() const {return prot_mem; }
    void memfcn(Base &b) { b =* this; }

};

struct Derived_from_Public : public Pub_Derv {
    int use_base() {return prot_mem; }
    void memfcn(Base &b) { b = *this; }

};

struct Derived_from_Protected : public Prot_Derv {
    int use_base() {return prot_mem; }
    void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Private : public Priv_Derv {
    //错误：Base::prot_mem在Priv_Derv中是private
    //int use_base() {return prot_mem; }

    //void memfcn(Base &b) { b = *this; }

};


int main(int argc, char **argv){
    Pub_Derv d1;
    Priv_Derv d2;
    Prot_Derv d3;
    Derived_from_Public dd1;
    Derived_from_Private dd2;
    Derived_from_Protected dd3;
    d1.pub_mem();
    //d2.pub_mem(); 错误
    //d3.pub_mem(); 错误
    Base *p = &d1;
    //p=&d2; //错误
    //p=&d3; 错误
    p=&dd1;
    ///p=&dd2; 错误
    //p=&dd3; 错误

}