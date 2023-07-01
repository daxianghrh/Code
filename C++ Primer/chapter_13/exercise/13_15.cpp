/* 
假定numbered定义了一个拷贝构造函数，能生成一个新的序号。
这会改变上一题中调用的输出结果吗？

答：会
 */
#include<iostream>
using namespace std;

class numbered{
friend void f(numbered s);
public:
    numbered(){
        mysn=++cnt;
    }
    numbered(const numbered &n){
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
    //输出: 4 5 6
    return 0;
}
