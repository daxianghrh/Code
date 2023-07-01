#ifndef __12__H_
#define __12__H_

#include<iostream>
#include<vector>
#include<memory>
using namespace std;

class StrBlobPtr;
class StrBlob{

friend class StrBlobPtr;

public:
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);

    size_type size() const{
        return data->size();
    }

    bool empty() const{
        return data->empty();
    }  
    //添加元素
    void push_back(const string &t){
        data->push_back(t);
    }
    //删除元素
    void pop_back();

    //元素访问
    string& front();
    string& back();

    const string& front() const;
    const string& back() const;

    //返回指向首元素和尾后元素的StrBlobPtr
    StrBlobPtr begin();
    StrBlobPtr end();

private:
    shared_ptr<vector<string>> data;

    //若data[i]不合法，抛出一个异常
    void check(size_type i,const string &msg) const;

};


//对于访问一个不存在元素的尝试，StrBlobPtr抛出一个异常
class StrBlobPtr{
public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob &a,size_t sz=0):wptr(a.data),curr(sz){}
    bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }
    string& deref() const;
    StrBlobPtr& incr();//前缀递增


private:
    //若检查成功，check返回一个指向vector的shared_ptr
    shared_ptr<vector<string>> check(size_t,const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;//在数组中的位置
};


#endif