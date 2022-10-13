#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool buddyStrings(string s, string goal) {
        //枚举
        unordered_map<char,int> cimap;
        int first = -1, second = -1;
        //s和goal长度比较
        if(s.size() != goal.size()){
            return false;
        }
        //s == goal ?
        if(s == goal){
            //判断s中是否有字母出现两次以上
            for(auto &c : s){
                if(cimap.count(c)){
                    return true;
                }
                ++cimap[c];     
            }
            return false;
        }else{
            //s和goal只有两个位置的字母不同,其余位置都相同
            for(int i = 0; i < s.size(); ++i){
                if(s[i] != goal[i]){
                    if(first == -1){
                        first = i;
                    }else if(second == -1){
                        second = i;
                    }else{
                        return false;
                    }
                }
            }
        }
        //second != -1 保证两个不同
        return (second != -1 && s[first] == goal[second] && s[second] == goal[first]);
    }
};