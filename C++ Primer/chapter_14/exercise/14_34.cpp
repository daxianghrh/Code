#include<iostream>
using namespace std;

class Solution{
public:
    Solution(int a=2,int b=3,int c=4):a1(a),a2(b),a3(c){

    }
    const int& operator()(const int a,const int b,const int c) const{
        return a>0?b:c;
    }

private:
    int a1;
    int a2;
    int a3;
};


int main(){
    Solution s;
    int a=1,b=2,c=3;
    int ans=s(a,b,c);
    cout<<ans<<endl;
    return 0;
}