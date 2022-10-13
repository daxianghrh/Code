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
        //1、
        //vp.push_back(std::pair<std::string, int>(str, i));

        //2、
        //vp.push_back(make_pair(str, i));

        //3、
        vp.push_back({str, i});
    }
    for(const auto & v : vp){
        std::cout << v.first << " " << v.second << std::endl;
    }
}