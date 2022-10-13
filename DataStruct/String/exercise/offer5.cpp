#include <iostream>
#include <string>
using namespace std;
/**
 * @Descripttion: 剑指offer:替换空格
 * @Solution: 方法1:使用string::push_back,需要使用额外的辅助空间
 * @Solution: 方法2：不使用额外的辅助空间，扩容数组，双指针从后往前遍历
 */
class Solution1 {
public:
    string replaceSpace(string s) {
        string as;
        for (auto c : s) {
            if (c != ' ') {
                as.push_back(c);
            } else {
                as.push_back('%');
                as.push_back('2');
                as.push_back('0');
            }
        }
        return as;
    }
};

class Solution2 {
public:
    string replaceSpace(string s) {
        int length = s.size();
        cout << length << endl;
        int cntOfBlank = 0;
        for (auto c : s) {
            if (c == ' ') {
                ++cntOfBlank;
            }
        }
        s.resize(length + cntOfBlank * 2);
        cout << s.size() << endl;
        //双指针 i指向新数组的末尾，j指向旧数组的末尾
        for (int i = s.size() - 1, j = length - 1; j < i; --i, --j) { 
                if (s[j] == ' ') {
                    s[i] = '0';
                    s[i - 1] = '2';
                    s[i - 2] = '%';
                    i -= 2;
                } else {
                    s[i] = s[j];
                }
        }
        return s;
    }
};

int main() {
    Solution2 s2;
    string s = "we are happy.";
    string ans = s2.replaceSpace(s);
    cout << ans << endl;
}
