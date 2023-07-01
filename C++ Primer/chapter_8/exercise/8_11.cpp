#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

struct PersonInfo{
    std::string name;
    std::vector<std::string> phones;
};

int main(){
    std::string line, word;
    std::vector<PersonInfo> people;
    std::istringstream record;
    std::ifstream ifs("/home/hrh/Code/C++ Primer/chapter_8/exercise/PersonInfo.txt", std::ios::in);
    if(ifs.is_open()){
        std::cout << "成功打开文件" << std::endl;
    }else{
        std::cout << "文件打开失败" << std::endl;
    }
    while(std::getline(ifs, line)){
        PersonInfo info;
        record.clear();
        record.str(line);
        record >> info.name;
        while(record >> word){
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    for(auto &p : people){
        std::cout << p.name << " ";
        for(auto &q : p.phones){
            std::cout << q << " ";
        }
        std::cout << std::endl;
    }
}
