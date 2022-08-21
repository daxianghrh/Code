#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

bool myfun(const std::string &s){
    if(s.size() >= 5){
        return true;
    }else{
        return false;
    }
}

int main(){
    std::vector<std::string> words = {"hello world", "nihao", "bye", "m" , "n"};
    auto iter = partition(words.begin(),words.end(), myfun);
    auto i = words.begin();
    // while(i < iter){
    //     std::cout << *i << std::endl;
    //     ++i;
    // }
    for(auto i = words.begin(); i < iter; ++i){
        std::cout << *i << std::endl; 
    }
    getchar();
}