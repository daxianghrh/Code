#include <iostream>
#include <list>
#include <deque>

int main(){
    std::list<int> li = {1, 2, 3, 4, 5, 6 ,7,8};
    std::deque<int> di1, di2;
    for(auto i : li){
        if(i % 2 == 0){
            di1.push_back(i);
        }else{
            di2.push_back(i);
        }
    }
    for(auto i : di1){
        std::cout << i << std::endl;
    }
    for(auto i : di2){
        std::cout << i << std::endl;
    }
}