#include <iostream>
#include <vector>

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

class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double p, std::size_t qty_min, std::size_t qty_max, double disc) : Quote(book,p), min_qty(qty_min), max_qty(qty_max), discount(disc){}
    //覆盖基类的函数版本以实现基于大量购买的折扣策略
    double net_price(std::size_t) const override;

    //覆盖debug函数
    void debug() const override {
        cout << this->min_qty << ' ' << this->max_qty << ' ' << this->discount << endl;
    }
    
private:
    std::size_t min_qty = 0;//适用折扣的最低购买量
    std::size_t max_qty = 0;//适用折扣的最高购买量
    double discount = 0.0; //以小数表示折扣额
};


//如果达到了购买书籍的某个最低限度值，就可以享受折扣价；达到了最高购买量后原价购买
double Bulk_quote::net_price(size_t cnt) const {
    if(min_qty <= cnt <= max_qty){
        return cnt * (1-discount) * price;
    }else if(cnt > max_qty){
        return max_qty * (1 - discount) * price + (cnt - max_qty) * price;
    }
    return cnt * price;
}

int main(){
    Quote Q("emery",1.0);
    Q.debug();  
    Bulk_quote bq;
    bq.debug();
    return 0;
}