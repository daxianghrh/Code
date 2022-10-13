#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

int main()
{
    std::map<std::string, std::vector<int>> msi;
    auto ret = msi.insert({"hello", {1, 2, 3}});

}