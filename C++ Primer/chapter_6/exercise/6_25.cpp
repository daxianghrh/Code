/* 
问题：编写一个main函数，令其接受两个实参。把实参的内容连接成一个string对象并输出出来
 */
#include<iostream>
#include<string>
using namespace std;
//命令行传参 第一个参数是可执行文件的名字 第二个参数是you 第三个参数i
//hrh@hrh-ubuntu:~/Code$ ./6_25.out you i he
int main(int argc,char *argv[]){//C语言风格  指针char **argv
    string s;
    for(auto i=1;i!=argc;++i){
        s+=argv[i];
    }
    cout<<s<<endl;
    //输出 youihe
    return 0;
}