#include <list>
#include <iostream>

int main(){
    std::list<int> lst1;
    std::list<int>::iterator iter1 = lst1.begin(), iter2 = lst1.end();
    //迭代器没有 < 运算符
    // while(iter1 < iter2){

    // }
    while(iter1 != iter2 ){

    }
}