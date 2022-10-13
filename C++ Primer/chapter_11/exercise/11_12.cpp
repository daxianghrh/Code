#include <iostream>
#include <string>
#include <vector>
#include <utility>


int main()
{
    std::vector<std::pair<std::string, int>> vp;
    std::string str;
    int i;
    while(std::cin >> str >> i){
        vp.push_back(std::pair<std::string, int>(str, i));
    }
    for(const auto & v : vp){
        std::cout << v.first << " " << v.second << std::endl;
    }
}