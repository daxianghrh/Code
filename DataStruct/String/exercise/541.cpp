#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
/**
 * @Descripttion: 反转字符串-2
 * @Solution: 模拟  i += 2 * k
 */
class Solution {
public:
    string reverseStr(string s, int k) {
        int length = s.size();
        for (int i = 0; i < length; i += 2 * k) {
            reverse(s.begin() + i, s.begin() + min(i + k, length));
        }
        return s;
    }
};