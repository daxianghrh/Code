#include <iostream>
#include <vector>

std::vector<int>::iterator fun(std::vector<int>::iterator begin, std::vector<int>::iterator end, int& i)
{
    while(begin != end){
        if(*begin == i){
            return begin;
        }else{
            ++begin;
        }
    }
    return end;
}


int main(){
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    auto begin = v.begin();
    auto end = v.end();
    int i = 11;
    std::vector<int>::iterator ans =fun(begin, end, i);
    if(ans == end){
        std::cout << "未找到给定值" << std::endl;  
    }else{
        std::cout << "找到给定值：" << i << std::endl;
    }

}