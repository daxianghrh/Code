#include <iostream>
#include <vector>
#include <string>

int main(){
    char c;
    std::string s;
    s.reserve(120);
    while(std::cin >> c){
        s.push_back(c);
    }
    for(auto c : s){
        std::cout << c << std::endl;
    }
}