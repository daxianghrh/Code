#include<iostream>
#include<vector>
#include<string>
using namespace std;

// int main(){
//     int case=1;
//     switch (case)
//     {
//         case true:
//             string file_name;
//             int ival=0;
//             int jval;
//         case false: 
//             jval=next_num();
//             break;
//         default:
//             break;
//     }
// }

int main(){
    vector<string> vs;//存储输入流输入的string对象
    vector<int>v1;//存储对string对象的重复次数
    vector<string>v2;//存储string对象
    string s;
    int cnt=1;
    int m=1;//下面for循环无法统计最后一个string对象，定义一个变量充当最后一个string对象的标志位
    //输入若干string对象  ctrl+d结束
    while(cin>>s){
        vs.push_back(s);
    }
    for(auto it=vs.begin();(it+1)!=vs.end();++it){
        //前后两个相邻的string对象相同
        if(*it==*(it+1)){
            ++cnt;
            ++m;
        }else{
            v1.push_back(cnt);
            cnt=1;
            v2.push_back(*it);
            m=1;
        }
    }
    v1.push_back(m);
    auto last=vs.cend();
    v2.push_back(*(last-1));
    int a=1;
    for(size_t i=0;i!=v1.size();++i){
        if(v1[i]>a){
            a=v1[i];
        }
    }
    if(a==1){
         cout<<"没有重复出现的单词"<<endl;
         return 0;
    }
    for(size_t i=0;i!=v1.size();++i){
        if(v1[i]==a){
            cout<<"单词"<<v2[i]<<"连续出现了"<<a<<"次"<<endl;
        }
    }
}
   

