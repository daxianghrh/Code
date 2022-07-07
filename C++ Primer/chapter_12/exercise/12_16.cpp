/*  
试图拷贝或赋值unique_ptr，编译器会给出什么错误？

*/
#include<iostream>
#include<memory>
using namespace std;

int main(){
    unique_ptr<string> p1(new string("123"));
    unique_ptr<string> p2;
    //p2=p1;
    //unique_ptr<string>p2(p1);
  
}