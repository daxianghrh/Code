#include <iostream>
#include <vector>

int main(){
    std::vector<int> vi = {1, 2, 3, 4};
    auto iter = vi.begin();
    auto iter2 = vi.end();
    vi.erase(iter2, iter2);
    for(auto i : vi){
        std::cout << i << std::endl;
    }
}