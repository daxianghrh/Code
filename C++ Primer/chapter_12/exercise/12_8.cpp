#include<iostream>


bool b(){
    int *p=new int;
    return p;
}
//p 将转换为 bool ，这意味着分配的动态内存没有机会被释放。
//结果，就会发生内存泄漏。

int main(){
    bool flag=b();
    std::cout<<flag<<std::endl;

}