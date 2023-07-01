#include <iostream>

void fun(int a){
    auto f = [a](int b){ return a + b;};
}

int main(){
    fun(5);
    getchar();
    return 0;
}