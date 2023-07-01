#include<iostream>
using namespace std;

//使用两层嵌套的for循环来处理多维数组的元素
int main(){
    constexpr size_t rosCnt=3,colCnt=4;
    int ia[rosCnt][colCnt]={
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12}
    };
    for(size_t i=0;i!=rosCnt;++i){
        for(size_t j=0;j!=colCnt;++j){
            ia[i][j]=i*colCnt+j;
            cout<<ia[i][j]<<" ";
        }
        cout<<endl;
    }

}