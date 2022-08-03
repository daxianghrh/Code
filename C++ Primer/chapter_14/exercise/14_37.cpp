#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class IsEqual{
public:
    IsEqual(int v):value(v){}

    bool operator()(int elements){
        return value==elements;
    }
private:
    int value;
};

int main(){
    vector<int> v={1,2,3,4,5,6,7};
    replace_if(v.begin(),v.end(),IsEqual(5),10);
    for(auto i:v){
        cout<<i<<endl;
    }   
}