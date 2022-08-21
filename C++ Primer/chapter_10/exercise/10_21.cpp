#include <iostream>
#include <algorithm>


int main()
{
    int a = 6;
    auto f = [&a] () -> bool { if(a == 0) return false;else return --a;};
    std::cout << f() << " " << a << std::endl;
    std::cout << f() << " " << a << std::endl;
    std::cout << f() << " " << a << std::endl;
    std::cout << f() << " " << a << std::endl;
    std::cout << f() << " " << a << std::endl;
    std::cout << f() << " " << a << std::endl;
    getchar();
} 