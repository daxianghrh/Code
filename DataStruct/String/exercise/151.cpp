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
ee *            第1步：删除多余的空格，比如首单词的前面、两单词中间多出的空格、末尾单词后面
 *            第2步：将整个字符串反转
 *            第3步：字符串反转后，每次单词的顺序也反转了，再将单词反转即可
 */
class Solution2 {
public:
    string reverseWords(string s) {
        eraseExtraBlank(s);
        rollBack(s, 0, s.size() - 1);
        int start = 0;
        for (int i = 0; i <= s.size(); ++i) {
            if ( i == s.size() || s[i] == ' ') {
                rollBack(s, start, i - 1);
                start = i + 1;
            }
        }
        return s;
    }

private:
    /**
     * @Descripttion: 删除多余空格
     * @param {string} &s
     */
    void eraseExtraBlank(string &s) {
        int slow = 0; //慢指针
        int length = s.size();
        for (int i = 0; i < length; ++i) {
            if (s[i] != ' ') { //当前索引值不是空格时处理，删除所有的空格
                if (slow != 0)
                    s[slow++] = ' '; //slow不是首字母，则需要添加一个空格
                while (i < length && s[i] != ' ') {
                    s[slow++] = s[i++];
                }  
            } 
        }
        s.resize(slow); //slow即长度
    }

    /**
     * @Descripttion: 反转，双指针
     * @param {string} &s
     * @param {int} start
     * @param {int} end
     */
    void rollBack(string &s, int start, int end) {
        for (int i = start, j = end; i < j; ++i, --j) {
            swap(s[i], s[j]);
        }
    }
};

