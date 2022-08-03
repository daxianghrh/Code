#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ReadString{
public:
    ReadString(istream &i=cin):in(i){

    }
    void operator() (){
        string str;
        while(getline(in,str)){
            vs.push_back(str); 
        }  
    }

    vector<string> vs;

private:
    istream &in;
    
};

int main(){
    ReadString r;
    r();
    for(auto s:r.vs){
        cout<<s<<endl;
    }
    return 0;
}