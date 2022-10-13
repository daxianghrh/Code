#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

class Solution {
public:
    vector<string> findOcurrences(string text, string first, string second) {
        vector<string> ans;
        istringstream iss(text);
        string word;
        //stack<string> ss;
        vector<string> vs;
        while(iss >> word){
            vs.push_back(word);
        }
        for(int i = 0; i < vs.size() - 2; ++i){
            if(vs[i] == first && vs[i+1] == second){
                ans.push_back(vs[i+2]);
            }
        }
        return ans;
    }
};