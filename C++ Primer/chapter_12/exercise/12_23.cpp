/* 
编写一个程序，连接两个字符串字面常量，将结果保存在一个动态分配的char数组中。
重写这个程序，连接两个标准库string对象
 */
#include<iostream>
#include<string>
#include<string.h>
using namespace std;


int main(){
    char *p=new char[10]();
    strcat(p,"hrh+");
    strcat(p,"tqq");
    cout<<p<<endl;
    delete [] p;
    string s1="1234";
    string s2="5678";
    cout<<s1+s2<<endl;




}

