/* 
定义一个简单的类，为该类定义拷贝构造、赋值函数和析构函数。
编写一个程序以不同方式使用X的对象：将它们作为非引用和引用参数传递；
动态分配它们;将它们存放于容器中。
 */

#include<iostream>
#include <vector>
#include <initializer_list>
using namespace std;


class X{
public:    
    //默认构造函数
    X(){
        cout<<"X()"<<endl;
    }

    //拷贝构造函数
    X(const X&){
        cout<<"X(const &)"<<endl;
    } 

    //拷贝赋值函数
    X& operator=(const X &x){
        cout<<"X& operator=(const X &x)"<<endl;
        return *this;
    }
    //析构函数
    ~X(){
        cout<<"~X()"<<endl;
    }
};

void f(const X &rx, X x)
{
    vector<X> vec;
    vec.reserve(2);
    vec.push_back(rx);
    vec.push_back(x);
}


int main(){
    X x1,x2;
    x1=x2;
    X *px=new X;
    f(*px,x1);
    delete px;
    return 0;
    //输出
    /*  
        X()
        X()
        X& operator=(const X &x)
        X()
        X(const &)
        X(const &)
        X(const &)
        ~X()
        ~X()
        ~X()
        ~X()
        ~X()
        ~X()
     */
}