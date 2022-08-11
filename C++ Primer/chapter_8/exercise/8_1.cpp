#include <iostream>

std::istream& fun(std::istream& is)
{
    int i;
    while(is >> i){
        std::cout << i << std::endl;
    }
    is.clear();
    return is;
}


int main()
{
    std::istream& is = fun(std::cin);
    std::cout << is.rdstate() << std::endl;
    return 0;   
}