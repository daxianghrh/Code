#include <iostream>
#include <deque>
#include <list>

int main(){
    std::list<std::string> sl;
    std::string s;
    while(std::cin >> s){
        sl.push_back(s);
    }
    for(auto iter = sl.begin(); iter != sl.end(); ++iter){
        std::cout << *iter << std::endl;
    }
    return 0;
}