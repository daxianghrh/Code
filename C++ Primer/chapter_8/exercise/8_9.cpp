#include <iostream>
#include <sstream>
std::istream& fun(std::istream& is)
{
    std::string i;
    while(std::getline(is, i)){
        std::cout << i << std::endl;
    }
    is.clear();
    return is;
}


int main()
{
    std::string s = "hello world";
    std::istringstream ss(s);
    std::istream& is = fun(ss);
    std::cout << is.rdstate() << std::endl;
}