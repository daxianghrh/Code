#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    string rsp;//作为循环的条件，不能定义在do的内部
    do
    {
        cout<<"请输入两个string对象"<<endl;
        string s1,s2;
        cin>>s1>>s2;
        if(s1.size()>=s2.size()){
            cout<<s2<<endl;
        }else{
            cout<<s1<<endl;
        }
        cout<<"想继续输入？是请输入yes，否输入no"<<endl;
        cin>>rsp;
    } while (!rsp.empty()&&rsp[0]!='n');//rsp为空或者输入no跳出循环
    
}