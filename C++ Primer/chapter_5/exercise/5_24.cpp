#include<iostream>
#include<vector>
#include<string>
using namespace std;


int main(){
    int v1,v2;
    cin>>v1>>v2;
    if(v2==0){
        throw runtime_error("被除数不能为0");
    }
    cout<<v1/v2<<endl;
    

    return 0;
}