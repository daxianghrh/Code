#include<iostream>
#include<memory>
using namespace std;

int main(){
    auto sp=make_shared<int>();
    auto p=sp.get();
    delete p;
    //doule free or corruption(out)
}