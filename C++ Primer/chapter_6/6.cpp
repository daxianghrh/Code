#include<iostream>
#include<string>
#include<vector>
#include<cassert>
using namespace std;
#define NDEBUG
#define assert(expr) (static_cast <bool> (expr) ? void (0) : __assert_fail (#expr, __FILE__, __LINE__, __ASSERT_FUNCTION))



//返回s中字符c第一次出现的位置索引
//引用形参occurs负责统计c出现的总次数
string::size_type find_char(const string &s,char c,string::size_type &occurs){
    auto ret=s.size();//若s中没有c 返回s的长度
    occurs=0;
    for(decltype(ret) i=0;i!=s.size();++i){
        if(s[i]==c){
            if(ret==s.size()){
                ret=i; //记录c第一次出现的位置
            }
            ++occurs;
        }
    }
    return ret;
}


void count(const string &,char ){   
    cout<<0<<endl;
}

void sum(vector<int>::iterator,vector<int>::iterator,int){
    cout<<1<<endl;
}

void print(const int ia[],size_t size){
    #ifndef NDEBUG
    cerr<<__func__<<":array size is"<<size<<endl;
    #endif

    #ifdef NDEBUG
    cout<<"array size is"<<size<<endl;
    #endif
}


void f(){
    cout<<"f()"<<endl;
};
void f(int){
    cout<<"f(int)"<<endl;
};
void f(int,int){
    cout<<"f(int,int)"<<endl;
};
void f(double,double=3.15){
    cout<<"f(double,double)"<<endl;
};

int fcn(int,int){

};


int main(){
    int ia[]={1,2,3,4,5,6,7,8,9,10};
    print(ia,sizeof(ia)/sizeof(ia[0]));

    //f(42,2.56);
    //f(2.55,42);
    f(42);
    f(42,0);
    f(2.56,3.14);

    int (*pf)(int,int)=fcn;
    vector<decltype(pf) *> vpf;
    


    return 0;
}




