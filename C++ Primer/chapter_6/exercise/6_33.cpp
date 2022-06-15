/* 
问题：编写一个递归函数，输出vector对象的内容

 */
#include<iostream>
#include<vector>
using namespace std;



void printVector(const vector<int>::iterator iter,const vector<int>::iterator end){
    if(iter!=end){
        cout<<*iter<<endl;
        printVector(iter+1,end);
    }
    
}



int main(){
    int ia[4]={1,2,3,4};
    vector<int> v(ia,ia+4);
    auto begin=v.begin(),end=v.end();
    printVector(begin,end);

}

