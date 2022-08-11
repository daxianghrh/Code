#include <iostream>
#include <vector>
#include <fstream>

void fun(std::ifstream& ifs)
{
    std::vector<std::string> v;
    std::string str;
    ifs.open("/home/hrh/Code/C++ Primer/chapter_8/exercise/8_4.txt");
    if(ifs){
        std::cout << "成功打开文件" << std::endl;
    }else{
        std::cerr << "未成功打开文件" << std::endl;
    }
    while(ifs >> str){ //忽略回车和空格符号
        v.push_back(str);
    }
    //以空格为分隔符，每行读取
    // while(std::getline(ifs, str, ' ')){
    //     v.push_back(str);
    // }
    for(const auto &s : v){
        std::cout << s <<std::endl;
    }
}


int main(){
    std::ifstream ifs;
    fun(ifs);
    return 0;
}