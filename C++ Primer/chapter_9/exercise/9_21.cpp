#include <iostream>
#include <vector>


int main(){
    std::vector<std::string> vs;
    auto iter = vs.begin();
    std::string word;
    while(std::cin >> word){
        iter = vs.insert(iter, word);
    }
    for(auto s : vs){
        std::cout << s << std::endl;
    }
}