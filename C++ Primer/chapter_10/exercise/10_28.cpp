#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>

int main()
{
    std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> li1, li2, li3;
    copy(vi.begin(), vi.end(), back_inserter(li1));
    for(auto i : li1){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    copy(vi.begin(), vi.end(), front_inserter(li2));
    for(auto i : li2){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    copy(vi.begin(), vi.end(), inserter(li3,li3.begin()));
    for(auto i : li3){
        std::cout << i << " ";
    }
    std::cout << std::endl;
}