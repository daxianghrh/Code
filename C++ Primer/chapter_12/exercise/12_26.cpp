#include<iostream>
#include<string>
#include<memory>
using namespace std;


int main(){
    size_t n=5;
    allocator<string> alloc;
    auto const p=alloc.allocate(n);
    string s;
    auto q=p;
    while(cin>>s&&q!=p+n){
        alloc.construct(q++,s);
    }
    while(q!=p){
        cout<<*--q<<endl;
        alloc.destroy(q);
    }
    alloc.deallocate(p,n);
}