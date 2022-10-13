#include <iostream>
#include <vector>
using namespace std;
/**
 * @Descripttion: 反转字符串
 * @Solution: 双指针
 */
class Solution {
public:
    void reverseString(vector<char>& s) {
        int l = 0, r = s.size() - 1;
        for (l, r; l <= r; ++l, --r) {
            //交换
            char t = s[l];
            s[l] = s[r];
            s[r] = t;
        }
    }
};