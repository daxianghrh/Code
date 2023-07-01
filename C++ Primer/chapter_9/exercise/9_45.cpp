#include <iostream>
#include <string>

std::string& fun(std::string &name,std::string const &front, std::string const &back){
    name.insert(name.begin(), front.begin(), front.end());
    name.append(back);
    return name;
}

int main(){
    std::string name = "hu", front = "Mr.", back = "III";
    std::string &ans = fun(name, front ,back);
    std::cout << ans << std::endl;
}