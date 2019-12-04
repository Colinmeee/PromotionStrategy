#include<iostream> 

using namespace std;


class Cash
{
public:
    //����Ӧ�����
    virtual double AcceptCash(double money) = 0;
};

//8�۴�������
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

//��1000��200��������
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
 
 //200���ϲ��ִ�8�۴�������
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
    Cash* cs; //������������շѲ��� 
 
public:
    //��ʼ��ʱ���������Ĳ��Զ���
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
 
    //�õ��ֽ������
    double GetResult( double money )
    {
        return cs->AcceptCash(money);
    }
};

int main()
{
    double price;
    double number;
    int type;  // ����� 
 
    cout<<"�����뵥��: ";
    cin>>price;
 
    cout<<"����������: ";
    cin>>number;
 
    cout<<"��ѡ��������"<<endl
        <<"1 : ��8��"<<endl
        <<"2 : ��1000��200"<<endl
        <<"3 : 200���ϲ��ִ�8��"<<endl;
    cin>>type;
 
    try
    {
        CashContext cashcontext(type);
 
        cout<<"�ܼƣ�"<< price * number<<endl;
 
        cout<<"ʵ���ֽ�";
        cout<<cashcontext.GetResult( price * number )<<endl;
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }
 
    return 0;
}
