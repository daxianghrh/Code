#include <iostream>
#include <string>
#include <vector>

int main(){
    std::vector<char> vc = {'a', 'a', 'h', 'p', 'h'};
    std::string s(vc.begin(),vc.end());
    for(auto c : s){
        std::cout << c << std::endl;
    }
}