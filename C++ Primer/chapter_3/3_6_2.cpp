#include<iostream>
using namespace std;

//使用范围for语句处理多维数组 
int main(){
    constexpr size_t rosCnt=3,colCnt=4;
    size_t cnt=0;
    int ia[rosCnt][colCnt]={
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12}
    };
    for(auto &row:ia){
        for(auto &col:row){
            col=cnt;
            ++cnt;
            cout<<col<<" ";
        }
        cout<<endl;
    }
}

