/* 
编写一个函数，判读string对象中是否含有大写字母
编写另一个函数，把string对象全都改成小写形式
在这两个函数中你使用的形参类型相同吗?为什么？

*/
#include<iostream>
#include<string>
using namespace std;

bool isHaveUp(const string &s){//形参为常量引用
    for(string::size_type i=0;i!=s.size();++i){
        if(isupper(s[i])){
            return true;
        }
    }
    return false;
}

void toLower(string &s){ //形参为普通引用，需要修改对象s的值
    for(string::size_type i=0;i!=s.size();++i){
        s[i]=tolower(s[i]);
    }
}

int main(){
    bool flag=isHaveUp("heLLo world");
    cout<<flag<<endl;
    string s="ABCDEFGHJKLZ";
    toLower(s);
    for(const auto &c:s){
        cout<<c<<endl;
    }
    
    return 0;
}