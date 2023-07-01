/* 
编写函数，返回一个动态分配int的vector。将此vector传递给另一个函数，
这个函数读取标准输入，将读入的值保存在vector元素中。再将vector传递给另一个函数，
打印读入的值。记得在恰当的时刻delete vector
 */
#include<iostream>
#include<vector>
#include<memory>

using namespace std;

vector<int>* f1(){
    return new vector<int>();
}

void f2(vector<int> * a){
    int i;
    while(cin>>i){
        a->push_back(i);
    }  
}
void f3(vector<int> * a){
    for(const auto &v:*a){
        cout<<v<<endl;
    }
    delete a;
}

int main(){
   vector<int> *a=f1();
   f2(a);
   f3(a);
   return 0;

}