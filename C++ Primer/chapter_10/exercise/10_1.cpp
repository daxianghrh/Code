#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    std::vector<int> vi = {1, 2, 3, 5, 5, 6, 2, 5};
    int cnt = count(vi.cbegin(), vi.cend(), 5);
    std::cout << cnt << std::endl;
    system("pause");
}