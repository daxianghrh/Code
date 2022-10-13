#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans(nums1.size());
        //单调栈
        stack<int> st;
        //哈希表记录nums2数组中每个数所满足的下一个更大元素
        unordered_map<int, int> hashmap;
        for(int i = nums2.size() - 1; i >= 0; --i){
            int num = nums2[i];
            while(!st.empty() && num >= st.top()){
                st.pop();
            }
            hashmap[num] = st.empty() ? -1 : st.top();
            st.push(num);
        }
        for(int i = 0; i < nums1.size(); ++i){
            ans[i] = hashmap[nums1[i]];
        }
        return ans;
    }
};