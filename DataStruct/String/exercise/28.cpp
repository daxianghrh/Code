#include <iostream>
#include <string>
using namespace std;

/**
 * @Descripttion: 
 * @Solution: KMP模式匹配 
 */
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) 
            return 0;
        int i = 0, j = 0;
        int next[needle.size()];
        getNext(next, needle);
        for (int i = 0; i < haystack.size(); ++i) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                ++j; // i在for循环中+1
            }
            if ( j == needle.size()) {
                return i - needle.size() + 1;
            }
        }
        return -1;
    }
private:
    /**
     * @Descripttion: 求回溯next数组
     * @Solution: 
     * @param {int} next
     * @param {string} &s
     */
    void getNext(int next[], string &s) {
        int j = 0;
        next[0] = 0;
        for (int i = 1; i < s.size(); ++i) {
            while (j > 0 && s[i] != s[j]) {
                j = next[j -1];
            }
            if (s[i] == s[j]) {
                ++j;
            }
            next[i] = j;
        }
    }
};