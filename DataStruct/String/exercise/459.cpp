#include <iostream>
#include <string>
using namespace std;

/**
 * @Descripttion: 重复的子字符串
 * @Solution: 1、枚举法
 */
class Solution1{
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();
        bool match = false;
        for (int i = 1; i <= n/2; ++i) {
            if ( n % i == 0) {
                match = true;
                for (int j = i; j < n; ++j) {
                    if (s[j] != s[j - i]) {
                        match = false;
                        break;
                    }
                }     
            }
            if (match) {
                return true;
            }   
        }
        return false;
    }
};


/**
 * @Descripttion: 
 * @Solution: 2、移动匹配
 */
class Solution2 {
public:
    bool repeatedSubstringPattern(string s) {
        string ss = s + s;
        ss.erase(ss.begin());
        ss.erase(ss.end() - 1);
        if (ss.find(s, 0) != string::npos) {
            return true;
        } else {
             return false;
        }
    }
};

/**
 * @Descripttion: 
 * @Solution:  KMP算法
 */
class Solution3 {
public:
    bool repeatedSubstringPattern(string s) {
        
    }
};