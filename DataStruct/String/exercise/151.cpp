#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/**
 * @Descripttion: 反转字符串中的单词
 * @Solution: 使用sstream从string中读取单词
 */
class Solution {
public:
    string reverseWords(string s) {
        string ans;
        string word;
        vector<string> vs;
        //iss绑定到s上
        istringstream iss(s);
        while (iss >> word) {
           vs.push_back(word);
        }
        for (int i = vs.size() - 1; i > 0; --i) {
            ans += vs[i] += " ";
        }
        ans += vs[0];      
        return ans;      
    }
};

/**
 * @Descripttion: 
 * @Solution: 不使用辅助空间，如何解决？
 */
class Solution2 {
public:
    string reverseWords(string s) {

    }
};

