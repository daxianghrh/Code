/* 
若f的参数是const numbered&，将会怎样？这会改变输出结果吗？
若会改变，为什么？新的输出结果是什么?

答：
 */
#include<iostream>
using namespace std;

class numbered{
friend void f(const numbered &s);
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

void f(const numbered &s){
    cout<<s.mysn<<endl;
}

int numbered::cnt=0;

int main(){
    numbered a,b=a,c=b;
    f(a);
    f(b);
    f(c);
    //输出: 1 2 3 
    return 0;
}