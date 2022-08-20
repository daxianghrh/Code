#include <iostream>
#include <list>
#include <vector>

int main(){
    int ia[] = {0, 1 , 1, 2, 3, 5, 8, 13, 21, 55, 89};
    std::vector<int> vi(ia, std::end(ia));
    std::list<int> li(vi.begin(), vi.end());
    auto vbegin = vi.begin();
    auto lbegin = li.begin();
    while(vbegin != vi.end() && lbegin != li.end()){
        if((*vbegin % 2) == 0){
            vbegin = vi.erase(vbegin);
            ++lbegin;
        }else{
            lbegin = li.erase(lbegin);
            ++vbegin;
        }
    }
    for(auto i : vi ){
        std::cout << i << std::endl;
    }
    std::cout << "--------------" << std::endl;
    for(auto i : li){
        std::cout << i << std::endl;
    }
}