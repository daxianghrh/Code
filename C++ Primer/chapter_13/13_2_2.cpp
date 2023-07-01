#include<iostream>
#include<string>
using namespace std;


class HasPtr{
    friend void swap(HasPtr&,HasPtr&);
public:
    //将计数器置为1
    HasPtr(const string &s=string()):ps(new string(s)),i(0),use(new size_t(1)){}
    //拷贝三个数据成员，并递增计数器
    HasPtr(const HasPtr &p):ps(p.ps),i(p.i),use(p.use){
        ++*use;
    }
    //拷贝赋值构造函数
    HasPtr& operator=(const HasPtr&);
    //析构函数
    ~HasPtr();

private:
    string *ps;
    int i;
    size_t *use;//用来记录有多少个对象共享*ps的成员
};

HasPtr::~HasPtr(){
    if(--*use==0){
        delete ps;//释放string内存
        delete use;//释放计数器内存
    }
}

HasPtr& HasPtr::operator=(const HasPtr &rhs){
    ++*rhs.use;
    //递减左侧对象的引用计数
    if(--*this->use==0){
        delete ps;
        delete use;
    }
    ps=rhs.ps;
    i=rhs.i;
    use=rhs.use;
    return *this;  
}

inline void swap(HasPtr &lhs,HasPtr &rhs){
    using std::swap;
    swap(lhs.ps,rhs.ps);//交换指针，而不是string成员
    swap(lhs.i,rhs.i);//交换int成员
}