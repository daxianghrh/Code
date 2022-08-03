/* 
    拷贝控制示例
 */
// #ifndef _13_4_H_
// #define _13_4_H_

#include<iostream>
#include<set>
#include<string>
using namespace std;

//Message类
//提供save和remove操作，向给定的Folder添加一条Message或删除一条Message

class Folder;
class Message{
    friend class Folder;
public:
    //folders被隐式初始化为空集
    explicit Message(const string &str=""):contents(str){}
    
    Message(const Message &m);

    Message& operator=(const Message &rhs);

    ~Message();

    //save和remove成员
    //save将本Message存放在给定Folder中；remove,删除本Message
    void save(Folder &f);
    void remove(Folder &f);
private:
    string contents; //实际消息文本
    set<Folder*> folders;//包含本Message的Folder
    
    //拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
    //将本Message添加到指向参数的Folder中
    void add_to_Folders(const Message&);
    //从folders中的每个Folder中删除本Message
    void remove_from_Folders();

    //向folders添加或删除一个给定的Folder*
    void add_Folder_to_folders(Folder *f);
    void remove_Folder_from_folders(Folder *f);


};


//Folder类
//提供addMsg和remMsg成员，完成在给定Folder对象的消息集合中添加和删除Message的工作
class Folder{
    friend class Message;
public:
    Folder()=default;
    Folder(const Folder &);
    Folder& operator=(const Folder &);
    ~Folder();

    //addMsg和remMsg成员
    //添加给定Message的指针
    void addMsg(Message *);
    //删除给定Message的指针
    void remMsg(Message *);

private:
    set<Message*> messages; //本Folder所包含的Message
};





// #endif