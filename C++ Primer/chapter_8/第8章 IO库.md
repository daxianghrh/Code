# 第8章 IO库

## 8.1 IO类

| 头文件 |类型|
|----|----|
|iostream|定义了读写流的基本类型|
|fstream|定义了读写命名文件的类型|
|sstream|定义了读写内存string对象的类型|

#### IO类型间的关系

继承机制

#### 8.1.1 IO对象无拷贝或赋值

不能拷贝IO对象，因此不能将形参或返回类型设置为流类型。进行IO操作的函数通常以引用方式传递和返回流。读写一个IO对象会改变其状态，因此传递和返回的引用都不能是const的。

#### 8.1.2 条件状态

##### 查询流的状态

#### 8.1.3 管理输出缓冲

##### 刷新输出缓冲区

操纵符endl可以完成换行并刷新缓冲区的工作。IO库还有两个类似的操纵符：flush和ends。flush刷新缓冲区，但不输出任何额外的字符;ends向缓冲区插入一个空字符，然后刷新缓冲区。

##### unibuf操纵符

若想在每次输出操作后都刷新缓冲区，可以使用unitbuf操纵符。它告诉流在接下来的每次写操作都执行一次flush操作。而nounibuf操纵符则重置流，使其恢复使用正常的系统管理的缓冲区刷新机制：

```cpp
cout << unibuf;//所有输出操作都会立即刷新缓冲区
//任何输出都立即刷新，无缓冲
cout << nounitbuf；//回到正常的缓冲方式
```


## 8.2 文件输入输出

头文件fstream定义了三个类型来支持文件IO：**ifstream**从一个给定文件读取数据，**ofstream**向一个给定文件中写入数据，以及**fstream**可以读写文件。

### 8.2.1 使用文件流对象

```cpp
ifstream in("file.txt");//构造一个ifstream对象，从文件file.txt中读取数据
ofstream out;//输出文件流未关联到任何文件
```

#### 用fstream代替iostream&

由于IO类型的继承机制，在要求使用基类型对象的地方，我们可以使用继承类型的对象来替代。这意味着，接受一个iostream类型引用(或指针)参数的函数，可以用一个对应的fstream(或sstream)类型来调用。

#### 成员函数open和close

#### 自动构造和析构

注：当一个fstream对象被销毁时，close会自动被调用

### 8.2.2 文件模式

每个流都有一个关联的**文件模式**,用来指出如何使用文件。
|文件模式|解释|
|----|----|
|ios::in|从文件中读取数据|
|ios::out|向文件中写入数据|
|ios::ate|打开文件后立即定位到文件末尾|
|ios::app|每次写操作前均定位到文件末尾|
|ios::trunc|截断文件|
|ios::binary|以二进制方式读写文件|

#### 以out模式打开文件会丢弃已有数据

打开一个ofstream时，文件的内容会被丢弃。阻止一个ofstream清空给定文件内容的方法是同时指定app模式。

#### 每次调用open时都会确定文件模式

注：每次打开文件时，都要设置文件模式，可能是显式地设置，也可能是隐式地设置。当程序未指定模式时，就使用默认值。例如：ofstream未指定文件打开模式，默认是ios::out，通常情况下out模式意味着同时使用trunc模式。

## 8.3 string流

sstream头文件定义了三个类型来支持内存IO：**istringstream**从一个给定字符串读取数据，**ostringstream**向一个给定字符串写入数据，以及**stringstream**可以读写字符串。sstream继承于iostream，除了继承得来的操作，还有如下的成员函数：
```cpp
sstream ss;//构造一个stringstream对象
sstream strm(s);//构造一个stringstream对象，保存string s的一个拷贝
strm.str();//返回strm所保存的string的拷贝
strm.str(s);//将string s拷贝到strm中，返回void

```

### 8.3.1 使用istringstream

当我们的某些工作是对整行文本进行处理，而其他一些工作是处理行内的单词时，通常可以使用istringstream。

```cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

struct PersonInfo{
    std::string name;
    std::vector<std::string> phones;
};

int main(){
    std::string line, word;
    std::vector<PersonInfo> people;
    std::istringstream record;
    std::ifstream ifs("/home/hrh/Code/C++ Primer/chapter_8/exercise/PersonInfo.txt", std::ios::in);
    if(ifs.is_open()){
        std::cout << "成功打开文件" << std::endl;
    }else{
        std::cout << "文件打开失败" << std::endl;
    }
    while(std::getline(ifs, line)){
        PersonInfo info;
        record.clear();
        record.str(line);
        record >> info.name;
        while(record >> word){
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    for(auto &p : people){
        std::cout << p.name << " ";
        for(auto &q : p.phones){
            std::cout << q << " ";
        }
        std::cout << std::endl;
    }
}
```

### 8.3.2 使用ostringstream

当我们逐步构造输出，希望最后一起打印时，ostringstream很有用。