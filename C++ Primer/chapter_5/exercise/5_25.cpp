#include<iostream>
#include<vector>
#include<string>
using namespace std;


int main(){
    int v1,v2;
    while(cin>>v1>>v2){ 
    try{
        if(v2==0){
        throw runtime_error("被除数不能为0");
        }
        cout<<v1/v2<<endl;
    }
    catch(runtime_error err){
        cout<<err.what()<<"是否重新输入新数并重新执行try语句? y n"<<endl;
        char c;
        cin>>c;
        if(!cin||c=='n'){
            break;
        }
    }   
    }
    return 0;
}