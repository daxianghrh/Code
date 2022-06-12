/* 
问题：编写一个函数，令其接受两个参数：一个是int型的数，另一个是int指针。
    函数比较int的值和指针所指的值，返回较大的那个。在该函数中指针的类型应该是什么？
*/
#include<iostream>
using namespace std;

int bigInt(const int a,const int *p){ 
    if(a>=*p){
        return a;
    }else{
        return *p;
    }
}

int main(){
    int a=1,b=2,ans;
    ans=bigInt(a,&b);
    cout<<ans<<endl;
    return 0;
}