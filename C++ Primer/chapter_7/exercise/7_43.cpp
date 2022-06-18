#include<iostream>
#include<vector>
using namespace std;

class NoDefault{
public:
    NoDefault(int i){}
};


class C{
public:
    //C(){} 错误：NoDefault没有默认构造
    C():def(0){}
private:
    NoDefault def;
};



int main(){
    C c;
    //vector<NoDefault>v(10); 不合法 NoDefault没有默认构造
    vector<C> v(10);//合法 
    return 0;

}