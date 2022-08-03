/* 
    抽象基类
 */
#include <iostream>
#include <vector>
#include <memory>
#include <set>

using namespace std;

class Quote{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price){}
    
    std::string isbn() const {return bookNo;}
    //返回给定数量的书籍地销售总额
    //派生类负责改写并使用不同的折扣计算算法
    virtual double net_price(std::size_t n) const {return n * price; }

    //显示每个类的数据成员
    virtual void debug() const {
        cout << this->bookNo << ' ' << this->price << endl;
    }

    virtual ~Quote() = default; //对析构函数进行动态绑定

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

//用于保存折扣值和购买量的类，派生类使用这些数据
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty) ,discount(disc) {}
    
    double net_price(std::size_t n) const = 0;

    std::pair<size_t, double> discount_policy() const { return {quantity, discount}; }
protected:
    std::size_t quantity = 0.0;//折扣适用的购买量
    double discount = 0.0;//折扣的小数值
};

//重新实现Bulk_quote,继承Disc_quote而非直接继承Quote
//当同一书籍的销售量超过某个值时启用折扣
//折扣的值是一个小于1的正的小数值，以此来降低正常销售价格
class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc){}

    //覆盖基类中的函数版本以实现一种新的折扣策略
    double net_price(std::size_t) const override;
};

double Bulk_quote::net_price(std::size_t cnt) const {
    if(quantity <= cnt){
        return quantity* price;
    }else 
        return quantity * (1 - discount) * price;
}


class Basket {
public:
    //Basket使用合成的默认构造函数和拷贝构造函数
    void add_item(const std::shared_ptr<Quote> &sale) {
        items.insert(sale);
    }

    double total_receipt(ostream &os) const;

private:
    //该函数用于比较shared_ptr，multiset成员会用到它
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs){
        return lhs->isbn() < rhs->isbn();
    }
    //multiset保存多个报价，按照compare成员排序
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};

double Basket::total_receipt(ostream &os) const 
{
    double sum = 0.0;
    //iter指向ISBN相同的一批元素中的第一个
    //upper_bound返回一个迭代器，该迭代器返回指向这批元素的尾后位置
    for(auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter , items.count(*iter));
    }
    os << "Total Sale: " << sum << endl;
    return sum;
}






int main(int argc, char **argv){
    std::vector<Quote> vq;
    double sum = 0.0;
    vq.push_back(Bulk_quote("0-201-54848-7", 50, 10, 0.25));
    vq.push_back(Bulk_quote("0-201-54848-8", 60, 10, 0.25));
    for(auto q : vq){
        sum += q.net_price(40);
    }
    std::cout << sum << std::endl;//4400

    std::vector<std::shared_ptr<Quote>> vsq;
    double sum2 = 0.0;
    vsq.push_back(std::make_shared<Bulk_quote>("0-201-54848-7", 50, 10, 0.25));
    vsq.push_back(std::make_shared<Bulk_quote>("0-201-54848-8", 60, 10, 0.25));
    for(auto q2 : vsq){
        sum2 += q2->net_price(40);
    }
    std::cout << sum2 << std::endl;//1100
}