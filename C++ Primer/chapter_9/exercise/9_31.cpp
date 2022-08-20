#include <iostream>
#include <list>
#include <forward_list>

int main(){
    std::list<int> li = {1, 2, 3, 4, 5, 6};
    std::forward_list<int> fsti = {2, 4, 7, 9, 10};
    auto lbegin = li.begin();
    auto fstbegin = fsti.begin();
    //list
    while(lbegin != li.end()){
        if(*lbegin % 2 ){ //奇数
            lbegin = li.insert(lbegin,*lbegin);
            //lbegin += 2; list迭代器不存在 +=
            std::advance(lbegin,2);
        }else{
            lbegin = li.erase(lbegin);
        }
    }
    for(auto i : li){
        std::cout << i << std::endl;
    }

    //forward_list
    auto fstbegin_prev = fsti.before_begin();
    while(fstbegin != fsti.end()){
        if(*fstbegin % 2){
            fstbegin = fsti.insert_after(fstbegin_prev,*fstbegin);
            std::advance(fstbegin,2);
            std::advance(fstbegin_prev,2);
        }else{
            fstbegin = fsti.erase_after(fstbegin_prev);
        }
    }
    for(auto i : fsti){
        std::cout << i << std::endl;
    }

}