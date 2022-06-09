#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    string fs,s,pre_s;//定义string对象 
    if(cin>>fs){ //输入第一个string对象
        pre_s=fs;
        while(cin>>s){ //连续输入s
        // if(isupper(s[0])&&s==pre_s){
        //     cout<<s<<endl;
        //     break;
        // }
        // if(!isupper(s[0])||s!=pre_s){
        //     pre_s=s;
        //     cout<<"没有重复的单词"<<endl;
        if(!isupper(s[0])){
            cout<<"继续输入单词"<<endl;
            continue;
        }
        if(s==pre_s){
            cout<<s<<endl;
            break;
        }else{
            pre_s=s;
            cout<<"没有单词时连续出现"<<endl;
        }
        }
    }  
    return 0;
};