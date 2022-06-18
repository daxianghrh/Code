#include"7.h"

std::string Person::getName() const{
    return name;
}
std::string Person::getAddr() const{
    return addr;
}

istream &read(istream &is,Person &p){
    is>>p.name>>p.addr;
    return is;
}

ostream &print(ostream &os,const Person &p){
    os<<p.name<<""<<p.addr;
    return os;
}

Person::Person(){

}

Person::Person(const std::string  &s1,const std::string &s2="hfut"):name(s1),addr(s2){

}

int Person::some_member() const{
     return ++access_str;
}

void displayPerson(const Person &p){
    cout<<p.name<<p.addr<<endl;
}



int main(){
    Person p;
    int res=p.some_member();
    cout<<res<<endl;

    string s="huruohai";
    string s2("tongqianqian");
    //displayPerson(s2);
    //displayPerson("tongqianqian");
    //displayPerson("huruohai"); 错误：需要把定义的”huruohai“转换成string，再把string转换成Person
    //displayPerson(string("huruohai"));
    displayPerson(Person("huruohai"));
    //displayPerson(s);
    displayPerson(static_cast<Person>(s));
    return 0;
}