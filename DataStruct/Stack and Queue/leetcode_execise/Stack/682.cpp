#include <iostream>
#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    int calPoints(vector<string>& operations) {
        int ans = 0;
        stack<int> ss;
        for(int i = 0; i < operations.size(); ++i){
           //判断
           if(operations[i] == "+"){
                int t1 = ss.top();
                ss.pop();
                int t2 = ss.top();
                int t = t1 + t2;
                ss.push(t1);
                ss.push(t);
           }else if(operations[i] == "D"){
                int t = ss.top() * 2;
                ss.push(t);
           }else if(operations[i] == "C"){
                ss.pop();
           }else{
                ss.push(stoi(operations[i]));
           }
        }
        //求和
        while(!ss.empty()){
            ans += ss.top();
            ss.pop();
        }
        return ans;
          
    }
};