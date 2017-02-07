#pragma once
#include "fraction.h"
#include "unit.h"

template <typename... Es>
class Dimension
{
public:
    
    static void print(void)
    {
        std::cout << "{";
        (void)std::initializer_list<int> { (Es::print(), std::cout << ",", 0)... };
        std::cout << "\b}";
    }
        
};


template <typename, typename> class DimensionProductImpl;
template <typename, typename> class DimensionDivisionImpl;
template <typename, typename> class DimensionPowerImpl;

template <typename... E1s, typename... E2s>
class DimensionProductImpl<Dimension<E1s...>, Dimension<E2s...>>
{
public:
    typedef Dimension<FractionSum<E1s, E2s>...> dim;
};


template <typename... E1s, typename... E2s>
class DimensionDivisionImpl<Dimension<E1s...>, Dimension<E2s...>>
{
public:
    typedef Dimension<FractionSub<E1s, E2s>...> dim;
};

template <typename... E1s, typename f>
class DimensionPowerImpl<Dimension<E1s...>, f>
{
public:
    typedef Dimension<FractionProd<E1s, f>...> dim;
};



template <typename D1, typename D2> using DimensionProduct  = typename DimensionProductImpl<D1, D2>::dim;
template <typename D1, typename D2> using DimensionDivision = typename DimensionDivisionImpl<D1, D2>::dim;
template <typename D1, typename f>  using DimensionPower    = typename DimensionPowerImpl<D1, f>::dim;
template <typename D1>              using DimensionSqrt     = typename DimensionPowerImpl<D1, Fraction<1,2>>::dim;
template <typename D1>              using DimensionInverse  = typename DimensionPowerImpl<D1, Int<-1>>::dim;





template <unsigned int n, unsigned int i, typename... Es>
class SingleDimensionImpl
{
public:
    typedef typename SingleDimensionImpl<n, i-1, Int<i==(n+1)>, Es...>::dim dim;
};


template <unsigned int n, typename... Es>
class SingleDimensionImpl<n, 0, Es...>
{
public:
    typedef Dimension<Es...> dim;
};


template <unsigned int n, unsigned int i, typename... Es> using SingleDimension = typename SingleDimensionImpl<n, i, Es...>::dim;
