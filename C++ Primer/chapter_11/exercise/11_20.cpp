#include <iostream>
#include <string>
#include <map>
#include <algorithm>



int main()
{
    std::map<std::string, int> word_count;
    std::string str;
    int i;
    while(std::cin >> str ){
        auto ret = word_count.insert({str, 1});
        if(!ret.second){
            ++ret.first->second;
        }
    }
    for(const auto &i : word_count){
        std::cout << i.first << "occurs" << " " << i.second << ((i.second > 1) ? "times" : "time")  << std::endl;
    }
}