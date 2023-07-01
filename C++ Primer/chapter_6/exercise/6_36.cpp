/* 
问题：编写一个函数的声明，使其返回数组的引用并且该数组包含10个string对象。
    不要使用尾置返回类型、decltype或者类型别名
 */

#include<iostream>
#include<string>
#include<vector>
using namespace std;

string (&fun1(string (&s)[10]))[10]
{
    return s;

}
//使用类型别名
//typedef str_arr string[10];
using str_arr=string[10];
str_arr &fun2(str_arr &s){
    return s;
}


//使用decltype
string s[10] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "1"};
decltype(s) &fun3(decltype(s) &s){
    return s;
}


int main(){   
    string (&ds)[10] = fun1(s);
    ds[1] = "han";
    for (const auto &a : s)
    {
        cout << a << endl;
    }
    cout << endl;

    return 0;
}