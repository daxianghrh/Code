#include<iostream>
#include<memory>

using namespace std;


void process(shared_ptr<int> ptr){
    //使用ptr
    cout<<"inside process function:"<<ptr.use_count()<<endl;//2
}//ptr离开作用域，被销毁


int main(){
    shared_ptr<int> p(new int(42));
    process(shared_ptr<int>(p));

    cout<<p.use_count()<<endl;// 1 
    auto q = p;
    std::cout << p.use_count() << "\n";//2
    std::cout << "the int p now points to is:" << *p << "\n";//42
    
    //12.12
    auto p_=new int();
    auto sp=make_shared<int>();
    process(sp);
    //process(new int());//错误
    //process(p_);//错误：不存在从int *到shared_ptr
    process(shared_ptr<int>(p_));//临时的share_ptr传递给process
    
    return 0;
}