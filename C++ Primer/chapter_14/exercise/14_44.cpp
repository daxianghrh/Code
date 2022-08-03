/* 
    编写一个简单的桌面计数器使其能处理二元运算
 */
#include <iostream>
#include <functional>
#include <string>
#include <map>
using namespace std;

int add(int a, int b){
    return a+b;
}
auto mod=[](int i, int j){return i%j;};
class Caulate{
public:
    Caulate(std::map<std::string,function<int(int,int)>> binops) :binops(binops){}
    int operator() (int a, int b){
        return a*b;
    }
    std::map<std::string,function<int(int,int)>> binops;  
};

struct divide
{
    int operator() (int denominator, int divisor){
        return denominator/divisor;
    }
};

int main(int argc, char **argv){
    map<string,function<int(int,int)>> binops = {
    {"+",add},
    {"-",minus<int>()},
    {"/",divide()},
    {"*",[](int i, int j){return i*j;}},
    {"%",mod},
    {"*",Caulate(binops)}
};
    Caulate c(binops);
    int a=4,b=2;
    int ans=c.binops["+"](a, b);
    int ans2=c.binops["*"](10,2);
    cout<< ans << ' ' <<ans2 << endl;
}