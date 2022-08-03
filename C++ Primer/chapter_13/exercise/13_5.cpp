/*
给定下面的类框架，编写一个拷贝构造函数，拷贝所有成员。
你的构造函数应该动态分配一个新的string，并将对象拷贝到ps指向的位置，而不是ps本身的位置。
 */

#include<iostream>
#include<string>
using namespace std;

class HasPtr{
public:
    HasPtr(const string &s=string()):ps(new string(s)),i(0){}

    //拷贝构造函数 *hasPtr.ps得到字符串对象
    HasPtr(const HasPtr &hasPtr):ps(new string(*hasPtr.ps)),i(hasPtr.i){}

    //拷贝赋值函数
    HasPtr& operator=(const HasPtr &hasPtr) {
        string *new_ps=new string(*hasPtr.ps);
        delete ps;
        ps=new_ps;
        i=hasPtr.i;
        return *this;
    }

    //析构函数
    ~HasPtr(){
        delete ps;
    }
private:
    string *ps;
    int i;
};

