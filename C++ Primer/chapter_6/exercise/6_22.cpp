/* 
问题：编写一个函数，令其交换两个int指针
 */
#include<iostream>
using namespace std;

void swap(int *&p1,int *&p2){//指针的引用，这样会交换两个指针本身的值即地址
    int *temp=p1;
    p1=p2;
    p2=temp;
}


int main(){
    int a=1,b=2;
    int *p1=&a,*p2=&b;
    //交换前
    cout<<*p1<<*p2<<endl;
    swap(p1,p2);
    //交换后
    cout<<*p1<<*p2<<endl;
    return 0;
}