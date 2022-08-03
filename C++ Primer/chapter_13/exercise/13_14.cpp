/* 
假定numbered是一个类，它有一个默认构造函数，能为每个对象生成一个唯一的序号，
保存在名为mysn的数据成员中。假定numbered使用合成的拷贝控制成员。
 */
#include<iostream>
using namespace std;

class numbered{
friend void f(numbered s);
public:
    numbered(){
        mysn=++cnt;
    }

private:
    int mysn;
    static int cnt; //静态成员变量
};

void f(numbered s){
    cout<<s.mysn<<endl;
}

int numbered::cnt=0;

int main(){
    numbered a,b=a,c=b;
    f(a);
    f(b);
    f(c);
    //输出： 1 1 1
    return 0;
}