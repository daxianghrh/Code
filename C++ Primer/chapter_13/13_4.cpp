#include "13_4.h"

void Message::save(Folder &f){
    folders.insert(&f);//将给定Folder添加到我们的Folder列表中
    f.addMsg(this);//将本Message添加到f的Message集合中
}

void Message::remove(Folder &f){
    folders.erase(&f);
    f.remMsg(this);
}

//拷贝一个Message时，得到的副本应该与原Message出现在相同的Folder中
//遍历Folder指针的set，对每个指向原Message的Folder添加一个指向新Message的指针
//将本Message添加到指向m的Folder中
void Message::add_to_Folders(const Message &m){
    for(auto f:m.folders){
        f->addMsg(this);//向该Folder添加一个指向本Message的指针
    } 
}

//拷贝构造函数 
Message::Message(const Message &m):contents(m.contents),folders(m.folders){
    add_to_Folders(m);
}


//拷贝赋值运算符
Message& Message::operator=(const Message &rhs){
    //通过先删除指针再插入它们来处理自赋值的情况
    remove_from_Folders(); //更新已有Folder
    contents=rhs.contents;
    folders=rhs.folders;
    add_to_Folders(rhs); //将本Message添加到那些Folder中
    return *this;
}


void Message::remove_from_Folders(){
    for(auto f:this->folders){
        f->remMsg(this); //从该Folder中删除本Message
    }
}
//析构函数
Message::~Message(){
    remove_from_Folders();
}


void Folder::addMsg(Message *message){
    messages.insert(message);
}

void Folder::remMsg(Message *message){
    messages.erase(message);
}

void Message::add_Folder_to_folders(Folder *f){
    folders.insert(f);
}

void Message::remove_Folder_from_folders(Folder *f){
    folders.erase(f);
}
