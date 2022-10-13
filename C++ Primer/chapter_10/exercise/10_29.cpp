#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>


int main()
{
    std::ifstream ifs("/home/hrh/Code/C++ Primer/chapter_8/exercise/PersonInfo.txt");
    std::istream_iterator<std::string> iter_string(ifs), eof;
    std::vector<std::string> vs;
    while(iter_string != eof){
        vs.push_back(*iter_string++);
    }
    for(auto s : vs){
        std::cout << s << std::endl;
    }
}   