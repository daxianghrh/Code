//编写一个与用户交互的函数，要求用户输入一个数字，计算该数字的阶乘
#include<iostream>
using namespace std;
int fact(void){  
    int val;
    cout<<"请输入一个数字"<<endl;
    cin>>val;
    int ret=1;
    while(val>1){
        ret*=val;
        --val;
    }
    return ret;
}


int main(){ 
    int j=fact();
    cout<<j<<endl;
    return 0;
}