#include<iostream>
using namespace std;

class StrVec{
public:
    StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){};//allocator成员进行默认初始化
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();

    void push_back(const string&);//拷贝元素

    size_t size() const {return first_free-elements;}
    size_t capacity() const {return cap-elements;}

    string *begin() const {return elements;}
    string *end() const {return first_free;}
    


private:
    static allocator<string> alloc; //分配元素
    //被添加元素的函数使用
    void cheack_n_alloc(){
        if(size()==capacity()){
            reallocate();
        }
    }
    void free();//销毁元素并释放内存
    void reallocate();//获得更多内存并拷贝已有元素
    string *elements;
    string *first_free;
    string *cap;
};

