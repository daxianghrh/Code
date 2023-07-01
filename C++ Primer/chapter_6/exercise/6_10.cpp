/* 
编写一个函数使用指针形参交换两个整数的值。在代码中调用该函数并输出交换后的结果
*/
#include<iostream>
using namespace std;

void swap(int *p1,int *p2){
    int temp=*p1;
    *p1=*p2;
    *p2=temp;    
}


int main(){
    int a=4,b=2;
    cout<<"交换前："<<a<<b<<endl;
    swap(&a,&b);
    cout<<"交换后："<<a<<b<<endl;
    return 0;
}