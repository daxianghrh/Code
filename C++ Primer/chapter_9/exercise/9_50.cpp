#include <iostream>
#include <vector>
#include <string>

int main(){
    std::vector<std::string> vs = {"5.0", "6.8"};
    int sum1 = 0;
    float sum2 = 0;
    for(auto s : vs){
        sum1 += std::stoi(s);
        sum2 += std::stod(s);
    }
    std::cout << sum1 << std::endl;
    std::cout << sum2 << std::endl;

    return 0;
}