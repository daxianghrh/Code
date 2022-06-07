#include<iostream>
#include<vector>
#include<string>
using namespace std;


int main(){
    int i=0;
    cout<<i<<""<<++i<<endl;

    bool b=true;
    bool b2=-b;
    cout<<b<<b2<<endl;
    
    //溢出 short类型占16位 最大值为32767 最小值为-32768
    short short_value=32767;
    short_value+=1;
    cout<<short_value<<endl;

    int i2=21;
    int i3=-5;
    cout<<i2%i3<<endl;

    //int k={3.14};
    //cout<<k<<endl;

    int ival,jval;
    ival=jval=0;

    // int ival2,*p;
    // ival2=p=0;
    // string s1,s2;
    // s1=s2="OK";
    
    int ival3=0,j=0;
    j=++ival3;
    cout<<j<<ival3<<endl;
    j=ival3++;
    cout<<j<<ival3<<endl;
    
    vector<string>s={"a","b","c"};
    vector<string>::iterator iter=s.begin();
    *iter++;
    //(*iter)++;//不合法
    //*iter.empty();//不合法
    iter->empty();
    //++*iter;//不合法
    iter++->empty();
    // iter->empty();
    // iter++;
  
    int grade=80;
    cout<<((grade<60)?"fail":"pass")<<endl;
    cout<<(grade<60)?"fail":"pass";
    //cout<<grade<60?"fail":"pass";
    
    int x[10];
    int *p=x;
    cout<<sizeof(x)/sizeof(*x)<<endl;//10
    cout<<sizeof(p)<<endl;//8
    cout<<sizeof(*p)<<endl;//4
    cout<<sizeof(p)/sizeof(*p)<<endl;
    
    const char *pc;
    char *p=const_cast<char *>(pc);//正确：但是通过p写值是未定义的行为

    const char *cp;
    //char *cp=static_cast<char*>(cp);
    string str=static_cast<string>(cp);
    //string str2=const_cast<string>(cp);
    
    int *ip;
    char *pc=reinterpret_cast<char*>(ip);
    //string str(ip);
    return 0;
}