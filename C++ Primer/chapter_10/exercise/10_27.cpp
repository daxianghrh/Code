#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>

int main()
{
    std::vector<int> vi = {1, 2, 2, 3, 4, 4, 5, 6, 7, 6};
    std::list<int> li;
    sort(vi.begin(), vi.end());
    unique_copy(vi.begin(), vi.end(), back_inserter(li));
    for(auto i : li){
        std::cout << i << std::endl;
    }
}