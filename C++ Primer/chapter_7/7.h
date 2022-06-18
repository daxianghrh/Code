#ifndef __7_H__
#define __7_H__


#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Person{

friend istream &read(istream &is,Person &p);
friend ostream &print(ostream &os,const Person &p);
friend void displayPerson(const Person &p);
private:
    std::string name;
    std::string addr;
    
    mutable size_t access_str;
public:
    Person();
    explicit Person(const std::string &s1,const std::string  &s2);    

    std::string  getName() const;
    std::string  getAddr() const;

    int some_member() const;
};



class Person_mgr{
private:
    vector<Person> person{Person("huruohai","hfut")};
};



#endif