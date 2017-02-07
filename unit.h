#pragma once
#include "dimension.h"
#include "fraction.h"
#include "string.h"
#include "baseunit.h"



template <typename US, typename D, typename R = Int<1>, typename S = String::impl<'\0'>>
class Unit : public BaseUnit<S>
{
public:
    typedef D dim;


    static void printSystem(void)
    {
        std::cout << "[";
        US::print();
        std::cout << ", ";
        D::print();
        std::cout << ", ";
        R::print();
        std::cout << ", ";
        S::print();
        std::cout << "]";
    }

    static void printSymbol(void)
    {
      //  if ()
        S::print();
    }

    Unit(double value = 0.0)
    {
        m_value = value;
    }

    void print(std::ostream &f) const
    {
        f << m_value;
        Unit<US, D, R, S>::printSymbol();
    }

    double getValue(void) const
    {
        return m_value;
    }


    template <typename US2, typename D2, typename R2, typename S2>
    Unit<US, D, R, S>& operator=(const Unit<US2, D2, R2, S2>& q)
    {
        static_assert(Equals<US, US2>::ans && Equals<D, D2>::ans, "Error: units don't have the same dimension");

        m_value = q.getValue() * FractionDiv<R2, R>::value();
        return *this;
    }


private:
    double m_value;


};


template <typename US, typename D, typename R, typename S>
std::ostream& operator<<(std::ostream& f, Unit<US, D, R, S> const& u)
{
    u.print(f);
    return f;
}

template <typename US,
          typename D1, typename R1, typename S1,
          typename D2, typename R2, typename S2>
Unit<US, DimensionDivision<D1,D2>, FractionDiv<R1, R2>> operator/ (const Unit<US, D1, R1, S1>& q1, const Unit<US, D2, R2, S2>& q2)
{
    return Unit<US, DimensionDivision<D1,D2>, FractionDiv<R1, R2>>(q1.getValue() / q2.getValue());
}
