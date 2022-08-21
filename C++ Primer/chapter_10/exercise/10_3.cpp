#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

int main(){
    std::vector<double> vi = {1, 2, 3, 4, 5};
    int sum = accumulate(vi.cbegin(), vi.cend(), 0);
    std::cout << sum << std::endl;
    getchar();
}