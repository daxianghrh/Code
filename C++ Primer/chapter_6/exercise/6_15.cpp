/* 
问题:s是普通引用而occurs是普通引用？为什么s和occurs是引用类型而c不是？
    若s是普通引用会出现什么情况？若令occurs是常量引用会发生什么情况？

1、s是常量引用，因为我们不希望修改对象s的值，同时可以用字面值(如"hello")作为实参传递给形参；occurs是普通引用，统计c出现的次数，要求可以进行修改
2、不希望修改传入实参的值
3、s若是普通引用，则实参的类型受到限制，只能是string类型的对象，不能使用字面值("hello")等
4、occurs是常量引用，occurs的值不可以改变，就不能满足函数要求统计c出现的次数
*/


#include<iostream>
#include<string>
using namespace std;

//返回s中字符c第一次出现的位置索引
//引用形参occurs负责统计c出现的总次数
string::size_type find_char(const string &s,char c,string::size_type &occurs){
    auto ret=s.size();//若s中没有c 返回s的长度
    occurs=0;
    for(decltype(ret) i=0;i!=s.size();++i){
        if(s[i]==c){
            if(ret==s.size()){
                ret=i; //记录c第一次出现的位置
            }
            ++occurs;
        }
    }
    return ret; //出现次数通过occurs隐式地返回
}



int main(){
    string s="hhhhheeellohhafsdfsag";
    char c='h';
    string::size_type str;
    auto index=find_char(s,c,str);
    cout<<"字母:"<<c<<"出现次数为："<<str<<endl;
}