#include <iostream>
#include <algorithm>

int main(){
    auto f = [](int a, int b){ return a + b; };
    std::cout << f(2, 3) << std::endl;
    getchar();
}