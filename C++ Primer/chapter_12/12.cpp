#include "12.h"
#include<fstream>

//构造函数都使用初始化列表
StrBlob::StrBlob():data(make_shared<vector<string>>()){

}

StrBlob::StrBlob(initializer_list<string>il):data(make_shared<vector<string>>(il)){

}

//检查索引
void StrBlob::check(size_type i,const string &msg) const{
    if(i>=data->size()){
        throw out_of_range(msg);
    }
}

string& StrBlob::front(){
    check(0,"front on empty StrBlob");
    return data->front();
}

const string& StrBlob::front() const{
    check(0,"front on empty StrBlob");
    return data->front();
}

string& StrBlob::back(){
    check(0,"back on empty StrBlob");
    return data->back();
}

const string& StrBlob::back() const{
    check(0,"back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back(){
    check(0,"pop_back on empty StrBlob");
    data->pop_back();
}



StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

shared_ptr<vector<string>> StrBlobPtr::check(size_t i,const string &msg) const{
    auto ret=wptr.lock();//vector还存在吗
    if(!ret){
        throw runtime_error("unbound StrBlobPtr");
    }
    if(i>=ret->size()){
        throw out_of_range(msg);
    }
    return ret;//否则，返回指向vector的shared_ptr
}

string& StrBlobPtr::deref() const{
    auto p=check(curr,"dereference past end");
    return (*p)[curr];
}

//前缀递增：返回递增后的对象的引用
StrBlobPtr& StrBlobPtr::incr(){
    //如果curr已经指向容器的尾后位置，就不能在递增它
    check(curr,"increment past end of StrBlobPtr");
    ++curr;//推进当前位置
    return *this;
}

int main(){
    StrBlob b1;
    {
        StrBlob b2={"a","an","the"};
        b1=b2;
        b2.push_back("about");
    }
    //b2已经被摧毁了
    cout<<b1.size()<<endl; // 输出4 

   //12.20
    std::ifstream ifs("/home/hrh/Code/C++ Primer/chapter_12/book.txt");
    StrBlob blob;
    for (std::string str; std::getline(ifs, str); )
        blob.push_back(str);
    for (StrBlobPtr pbeg(blob.begin()), pend(blob.end()); pbeg != pend; pbeg.incr())
        std::cout << pbeg.deref() << std::endl;

    return 0;
}
