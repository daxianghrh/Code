/* 
问题：说明形参、局部变量以及静态变量的区别。编写一个函数,同时用到这三种形式

形参：定义在函数体内，由函数的实参来进行初始化，在执行完函数体后自动销毁
局部变量：定义在函数体内，需要自己定义初始化值，否则默认情况下值不确定，同样执行完函数体内代码后自动销毁
静态变量：定义在函数体内，局部变量声明前加上关键词static，同样需要自己定义初始值，执行完函数体内代码后不会销毁，会在整个程序结束后才销毁
 
*/
#include<iostream>
#include<vector>
using namespace std;

vector<int> test(int a,int b){ //形参
    int res=0;//局部变量
    res=a+b;
    vector<int> v;
    v.push_back(res);
    static size_t call_cnt=0;
    ++call_cnt;
    v.push_back(call_cnt);
    return v;
}


int main(){
    int a,b;//4 2
    cout<<"请输入两个整数"<<endl;
    cin>>a>>b;
    vector<int> ans;
    for(size_t i=0;i!=10;++i){
        ans=test(a,b);//res是局部变量，每次执行结果都为6;call_cnt第一次调用结束后为1，第二次调用后为2，依次递增。
    }
    for(const auto &i:ans){
        cout<<i<<endl;//6 10
    }

    return 0;
}
