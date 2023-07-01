#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    string fs,s,pre_s;//定义string对象 
    if(cin>>fs){ //输入第一个string对象
        pre_s=fs;
        while(cin>>s){ //连续输入s
        if(s==pre_s){
            cout<<s<<endl;
            break;
        }else{
            pre_s=s;
            cout<<"没有单词时连续出现的"<<endl;
        }
        }
    }  
    return 0;
}