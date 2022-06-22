#include <iostream>
//简单工厂模式
class Operation
{
protected:
    double num1;
    double num2;

public:
    void SetNums(double x, double y)
    {
        num1 = x;
        num2 = y;
    }
    virtual double GetResult()
    {
        double res = 0;
        return res;
    }
};
class OperationAdd : public Operation
{
public:
    double GetResult()
    {
        double res = num1 + num2;
        return res;
    }
};
class OperationSub : public Operation
{
public:
    double GetResult()
    {
        double res = num1 - num2;
        return res;
    }
};
class OperationMul : public Operation
{
public:
    double GetResult()
    {
        double res = num1 * num2;
        return res;
    }
};
class OperationDiv : public Operation
{
public:
    double GetResult()
    {
        if (num2 == 0)
        {
            std::cout << "error!";
            return 0;
        }
        double res = num1 / num2;
        return res;
    }
};
class OperationFactory
{
public:
    static Operation *CreatOperation(char operate)
    {
        Operation *oper = new Operation;
        switch (operate)
        {
        case ('+'):
            oper = new OperationAdd;
            break;
        case ('-'):
            oper = new OperationSub;
            break;
        case ('*'):
            oper = new OperationMul;
            break;
        case ('/'):
            oper = new OperationDiv;
        }
        return oper;
    }
};

//工厂模式
class IFactory
{
public:
    virtual Operation *CreatOperation() = 0;
};
class AddFactory : public IFactory
{
public:
    Operation *CreatOperation()
    {
        Operation *oper = new OperationAdd();
        return oper;
    }
};
class SubFactory : public IFactory
{
    Operation *CreatOperation()
    {
        Operation *oper = new OperationSub();
        return oper;
    }
};
class MulFactory : public IFactory
{
    Operation *CreatOperation()
    {
        Operation *oper = new OperationMul();
        return oper;
    }
};
class DivFactory : public IFactory
{
    Operation *CreatOperation()
    {
        Operation *oper = new OperationDiv();
        return oper;
    }
};
int main()
{
    IFactory *F = new DivFactory();
    Operation *A = nullptr;
    A = F->CreatOperation();
    A->SetNums(1, 5);
    double ans = A->GetResult();
    std::cout << ans;
    return 0;
}
