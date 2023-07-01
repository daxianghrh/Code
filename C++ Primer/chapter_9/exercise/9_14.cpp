#include <iostream>
#include <list>
#include <vector>
#include <string>

int main()
{
    std::list<const char*> l(5, "hello world");
    std::vector<std::string> vs;
    vs.assign(l.begin(), l.end());
    for(auto s : vs){
        std::cout << s << std::endl;
    }
}