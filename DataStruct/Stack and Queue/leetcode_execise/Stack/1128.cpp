#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        int ans = 0;
        int t = 0;
        unordered_map<int,int> iimap;
        //把[1,2] [2,1] 都转成12 统计12出现的次数
        for(auto &v : dominoes){
            t = (v[0] <= v[1] ? v[0] * 10 + v[1] : v[0] + v[1] * 10);
            ++iimap[t]; 
        }
        //遍历iimap
        for(auto & ii : iimap){
            //多米诺骨牌队要求是 i < j,从后往前排列组合对数应为cnt*(cnt - 1)/2
            ans += (ii.second * (ii.second - 1)) / 2;
        }
        return ans;
    }
};