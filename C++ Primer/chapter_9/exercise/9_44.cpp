#include <iostream>
#include <string>

void fun(std::string &s, std::string const &oldVal, std::string const &newVal){
    for(int pos = 0; pos <= (s.size() - oldVal.size());){
        if(oldVal == std::string(s, pos, oldVal.size())){
            s.replace(pos, oldVal.size(), newVal);
            pos += newVal.size();
        }else{
            ++pos;
        }
    }
}

int main(){
    std::string s("To drive straight thru is a foolish, tho courageous act.");
    fun(s, "tho", "though");
    fun(s, "thru", "through");
    std::cout << s << std::endl;

    return 0;
}