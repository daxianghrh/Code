#include <iostream>
#include <string>
#include <list>
#include <algorithm>

int main(){
    std::string s;
    std::list<std::string> ls;
    while(std::cin >> s){
        ls.push_back(s);
    }
    int cnt = count(ls.cbegin(), ls.cend(), "hello");
    std::cout << cnt << std::endl;
    getchar();
}