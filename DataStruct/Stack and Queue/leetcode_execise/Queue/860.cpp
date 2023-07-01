#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;


// class Solution {
// public:
//     bool lemonadeChange(vector<int>& bills) {
//         int a = 5, b = 10, c = 20;
//         unordered_map<int,int> iimap;
//         bool noUseTen = true;
//         for(auto &p : bills){
//             if(p == 5){
//                 ++iimap[a];
//             }else if(p == 10){
//                 if(iimap.count(5)){
//                     --iimap[a];
//                     ++iimap[b];
//                 }else{
//                     return false;
//                 }
//             }else{
//                 int cntOfFive = iimap.count(5);
//                 int cntOfTen = iimap.count(10);
//                 if(cntOfFive < 3){
//                     noUseTen = false;
//                 }
//                 if(cntOfFive >= 3 && noUseTen){
//                     iimap[5] -= 3;
//                 }else if(cntOfTen >= 1 && cntOfFive >= 1 && !noUseTen){
//                     --iimap[10];
//                     --iimap[5];
//                 }else{
//                     return false;
//                 }
//             }
//         }
//         return true;
//     }
// };