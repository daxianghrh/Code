/* 
问题：下面的函数合法吗？若合法，说明其功能；若不合法，修改其中的错误并解释原因

答：函数合法。
 */
#include<iostream>
using namespace std;

int &get(int *arry,int index){//非常量引用返回左值
    return arry[index];
}


int main(){
    int ia[10];
    for(int i=0;i!=10;++i){
        get(ia,i)=i;//用数组下标给函数返回值赋值，合法
    }
    for(const auto &i:ia){
        cout<<i<<endl;//输出0 1 2 3 4 5 6 7 8 9
    }
}