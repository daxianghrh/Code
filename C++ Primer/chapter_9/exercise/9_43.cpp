#include <iostream>
#include <string>

void fun(std::string &s, std::string const &oldVal, std::string const &newVal){
    for(auto curr = s.begin(); curr <= (s.end() - oldVal.size());){
        if(oldVal == std::string(curr, curr + oldVal.size())){
            curr = s.erase(curr, curr + oldVal.size());
            curr = s.insert(curr, newVal.begin(), newVal.end());
            curr += newVal.size();
        }else{
            ++curr;
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