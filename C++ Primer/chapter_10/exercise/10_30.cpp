#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>


int main()
{
    std::istream_iterator<int> in_iter(std::cin), eof;
    std::ostream_iterator<int> out_iter(std::cout, " ");
    std::vector<int> vi(in_iter,eof);
    sort(vi.begin(), vi.end());
    copy(in_iter, eof, out_iter);
    std::cout << std::endl;
}