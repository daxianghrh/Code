#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main(){
    std::vector<const char*> roster1 = {"hello", "nihao"};
    std::vector<const char*> roster2 = {"hello", "world"};
    bool ans = equal(roster1.cbegin(), roster1.cend(), roster2.cbegin());
    std::cout << ans ;
    getchar();
}