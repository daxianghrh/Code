/* 
下面的unique_ptr声明中，哪些是合法的，哪些可能导致后续程序出错?
解释原因
 */
#include<iostream>
#include<memory>
using namespace std;


int main(){
    int ix=1024,*pi=&ix,*pi2=new int(2048);
    typedef unique_ptr<int> IntP;

    //IntP p0(ix); 错误
    //IntP p1(pi); 编译可以通过，但是运行会报错。因为pi指针不是new分配的，当采用delete释放时，系统会报错
    //IntP p2(pi2);此代码可以编译，但在运行时会导致指针悬空。原因是unique_ptr将释放原始指针指向的对象。
    //IntP p3(&ix);当 unique_ptr 超出范围时，它会调用 delete 来释放一个没有使用 new 分配的对象。
    IntP p4(new int(2048));//正确
    // IntP p5(p2.get());运行时双重释放或损坏两个unique_ptr指向同一个对象。因此，当两者都超出范围时，操作系统将抛出双重释放或损坏。
}