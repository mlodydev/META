// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<class A>
class DExpr {
private:
    A a_;
public:
    DExpr()
    { }
    DExpr(const A& x)
        : a_(x)
    { }
    double operator()(double x) const
    {
        return a_(x);
    }
};

class DExprIdentity {
public:
    DExprIdentity()
    { }
    double operator()(double x) const
    {
        return x;
    }
};

template<class A, class B, class Op>
class DBinExprOp {
    A a_;
    B b_;
public:
    DBinExprOp(const A& a, const B& b)
        : a_(a), b_(b)
    { }
    double operator()(double x) const
    {
        return Op::apply(a_(x), b_(x));
    }
};

class DExprLiteral {
private:
    double value_;
public:
    DExprLiteral(double value)
    {
        value_ = value;
    }
    double operator()(double x) const
    {
        return value_;
    }
};

class DApAdd {
public:
    DApAdd() { }
    static inline double apply(double a, double b)
    {
        return a + b;
    }
};

class DApDivide {
public:
    DApDivide() { }
    static inline double apply(double a, double b)
    {
        return a / b;
    }
};

 //operator+(double, DExpr)
template<class A>
DExpr<DBinExprOp<DExprLiteral, DExpr<A>, DApAdd> >
operator+(double x, const DExpr<A>& a)
{
    typedef DBinExprOp<DExprLiteral, DExpr<A>, DApAdd> ExprT;
    return DExpr<ExprT>(ExprT(DExprLiteral(x), a));
}
// operator/(DExpr, DExpr)
template<class A, class B>
DExpr<DBinExprOp<DExpr<A>, DExpr<B>, DApDivide> >
operator/(const DExpr<A>& a, const DExpr<B>& b)
{
    typedef DBinExprOp<DExpr<A>, DExpr<B>, DApDivide> ExprT;
    return DExpr<ExprT>(ExprT(a, b));
}


template<class Expr>
void evaluate(DExpr<Expr> expr, double start, double end)
{
    const double step = 1.0;
    for (double i = start; i < end; i += step)
        std::cout << expr(i) << std::endl;
}

int main()
{
    DExpr<DExprIdentity> x; // Placeholder
    evaluate(x / (1.0 + x), 0.0, 10.0);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
