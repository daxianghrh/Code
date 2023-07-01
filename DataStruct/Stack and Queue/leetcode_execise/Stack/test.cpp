#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

// class Solution {
// public:
//     vector<string> findOcurrences(string text, string first, string second) {
//         vector<string> ans;
//         istringstream iss(text);
//         string word;
//         stack<string> ss;
//         while(iss >> word){
//             cout << word << endl;
//         }
//     }
// };

int main()
{
    // string s = "i  am  hrh ";
    // for(auto c : s){
    //     cout << c << endl;
    // }
    string s = "xu  zi  hao";
    istringstream iss(s);
    string word;
    while (iss >> word) {
        cout << word << endl;
    }

    if (s == "huruohai") return false;

    int c;
    cin >> c;
}