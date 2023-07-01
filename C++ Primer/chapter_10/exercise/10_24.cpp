#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>

bool check_size(const std::string &s, std::string::size_type sz)
{
    return s.size() < sz;
}

int main()
{
    std::vector<int> vi = {1, 2, 3, 4, 5, 7};
    std::string s = "nihao";
    auto iter = find_if(vi.begin(), vi.end(), std::bind(check_size, s, std::placeholders::_1));
    std::cout << *iter << std::endl;
    getchar();
    return 0;
}