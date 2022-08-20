#include <list>
#include <iostream>
#include <vector>

int main()
{
    std::list<int> l = {1, 2, 3, 4,5};
    auto lbegin = l.begin();
    auto lend = l.end();
    std::vector<double> vd(lbegin, lend);
    for(auto d : vd){
        std::cout << d << std::endl;
    }
    std::vector<int> vi(lbegin, lend);
    for(auto i : vi){
        std::cout << i << std::endl;
    }
}