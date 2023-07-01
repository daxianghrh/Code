#include <iostream>
#include <vector>

bool fun(std::vector<int>::iterator begin, std::vector<int>::iterator end, int& i)
{
    while(begin != end){
        if(*begin == i){
            return true;
        }else{
            ++begin;
        }
    }
    return false;
}


int main(){
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    auto begin = v.begin();
    auto end = v.end();
    int i = 8;
    bool ans =fun(begin, end, i);
    std::cout << ans << std::endl;
}