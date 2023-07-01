/* 
重做上一题，使用shared_ptr而不是内置指针
 */
#include<iostream>
#include<memory>
#include<vector>

using namespace std;

shared_ptr<vector<int>> f1(){
    return make_shared<vector<int>>();
}

void f2(shared_ptr<vector<int>> ptr_v){
    int i;
    while(cin>>i){
        ptr_v->push_back(i);
    }
}

void f3(shared_ptr<vector<int>> ptr_v){
    for(const auto &v:*ptr_v){
        cout<<v<<endl;
    }
}

int main(){
    shared_ptr<vector<int>> ptr_v=f1();
    f2(ptr_v);
    f3(ptr_v);
    return 0;
}