#include<iostream> 

using namespace std;


class Cash
{
public:
    //计算应付金额
    virtual double AcceptCash(double money) = 0;
};

//8折促销策略
class RebateStrategy : public Cash
{
private:
    double discount;
public:
    RebateStrategy( double dis ) : discount(dis)
     {
     }
 
    virtual double AcceptCash(double money)
    {
        return money * discount;
    }
};

//满1000减200促销策略
 class ReduceStrategy : public Cash
 {
private:
    double moneyLimit;
    double moneyMinus;
public:
    ReduceStrategy( double limit, double minus ) : moneyLimit(limit), moneyMinus(minus) {}
    
    virtual double AcceptCash(double money)
    {
        double result = money;
 
        if( money > moneyLimit )
        {
            result = money - 200;
        }
 
        return result;
    }
    
    
 };
 
 //200以上部分打8折促销策略
class PromotionalStrategy : public Cash
{
private:
    double moneyCondition;
    double discount;
public:
    PromotionalStrategy( double condition, double dis ) : moneyCondition(condition), discount(dis) {}
 
 
    virtual double AcceptCash(double money)
    {
        double result = money;
 
        if( money > moneyCondition )
        {
            result = 200+(money-200)*discount;
        }
 
        return result;
    }
};

class CashContext
{
private:
    Cash* cs; //声明付款金额的收费策略 
 
public:
    //初始化时，传入具体的策略对象
    CashContext(int type)
    {
        switch(type)
        {
        case 1:
            cs = new RebateStrategy(0.8);
            break;
        case 2:
            cs = new ReduceStrategy(1000,200);
            break;
        case 3:
            cs = new PromotionalStrategy(200, 0.8);
            break;
        default:
            exit(0);
        }
    }
 
    ~CashContext()
    {
        delete cs;
    }
 
    //得到现金计算结果
    double GetResult( double money )
    {
        return cs->AcceptCash(money);
    }
};

int main()
{
    double price;
    double number;
    int type;  // 活动类型 
 
    cout<<"请输入单价: ";
    cin>>price;
 
    cout<<"请输入数量: ";
    cin>>number;
 
    cout<<"请选择促销活动："<<endl
        <<"1 : 打8折"<<endl
        <<"2 : 满1000减200"<<endl
        <<"3 : 200以上部分打8折"<<endl;
    cin>>type;
 
    try
    {
        CashContext cashcontext(type);
 
        cout<<"总计："<< price * number<<endl;
 
        cout<<"实收现金：";
        cout<<cashcontext.GetResult( price * number )<<endl;
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }
 
    return 0;
}
