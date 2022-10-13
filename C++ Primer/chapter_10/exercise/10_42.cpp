#include <iostream>
#include <list>
#include <algorithm>


int main()
{
    std::list<std::string> ls = {"hello", "hello", "world", "nihao"};
    ls.sort();
    ls.unique();
    for(auto s : ls){
        std::cout << s << std::endl;
    }
}