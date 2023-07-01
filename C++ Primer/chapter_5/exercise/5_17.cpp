#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main(){
    vector<int>v1={0,1,1,2};
    vector<int>v2={0,1,1,2,3,5,8};
    size_t size1=v1.size();
    size_t size2=v2.size();
    size_t m=(size1>=size2)?size2:size1;
    bool flag;//标志位  是否是前缀数组
    if(m==size1){
        for(size_t i=0;i!=m;++i){
            if(v1[i]==v2[i]){
                flag=true;
                continue;
            }
            flag=false;
            break;
        }
    }else{
       for(size_t i=0;i!=m;++i){
            if(v2[i]==v1[i]){
                flag=true;
                continue;
            }
            flag=false;
            break;
        } 
    }
    cout<<flag<<endl;
};