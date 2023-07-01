#include <iostream>
#include <forward_list>

void fun(std::forward_list<std::string> &lst, std::string &s1, std::string &s2){
    auto prev = lst.before_begin();
    auto curr = lst.begin();
    while(curr != lst.end()){
        if(*curr == s1){//找到s1
            lst.insert_after(curr,s2);
            std::cout << "插入成功" << std::endl;
            return;
        }else{
            prev = curr;
            ++curr;
        }
    }
    //未找到s1
    lst.insert_after(prev, s2);
    std::cout << "未找到s1" << std::endl;
}

int main(){
    std::forward_list<std::string> flst = {"hello", "world", "nihao"};
    std::string s1 = "hrh";
    std::string s2 = "sb";
    fun(flst, s1, s2);
}