#include <iostream>
#include <deque>

int main(){
    std::deque<std::string> sd;
    std::string s;
    while(std::cin >> s){
        sd.push_back(s);
    }
    for(auto iter = sd.begin(); iter != sd.end(); ++iter){
        std::cout << *iter << std::endl;
    }
    return 0;
}