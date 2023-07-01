#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

int main()
{
    std::ifstream ifs("/home/hrh/Code/C++ Primer/chapter_8/exercise/8_4.txt", std::ios::in);
    std::string str;
    std::vector<std::string> vs;
    if(ifs.is_open()){
        std::cout << "成功打开文件" << std::endl;
    }else{
        std::cout << "文件打开失败" << std::endl;

    }
    while(std::getline(ifs, str)){
        std::istringstream ss(str);
        std::string s;
        vs.push_back(str);
        while(ss >> s){
            std::cout << s << std::endl;
        }       
    }
}