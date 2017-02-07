#pragma once

#include "baseunit.h"

template <unsigned int i, typename U, typename... Us>
class get
{
public:
    using type = typename get<i-1, Us...>::type;
};
 


template <typename U, typename... Us>
class get<0, U, Us...>
{
public:
    using type = U;
};


template <typename U, typename... Us>
class length
{
public:
    static const int ans = length<Us...>::ans + 1;
};

template <typename U>
class length<U>
{
public:
    static const int ans = 1;
};



template <typename... Us>
class UnitSystem;




template <typename, typename>
class DefaultUnitStringImpl;



template <typename U, typename... Us, typename E, typename... Es>
class DefaultUnitStringImpl<UnitSystem<U, Us...>, Dimension<E, Es...>>
{
private:
    typedef typename std::conditional
            <
                Equals<E,Int<0>>::ans,
                S("\0"),
                typename std::conditional
                <
                    Equals<E,Int<1>>::ans,
                    String::concat<typename U::symbol, S(".")>,
                    String::concat3<typename U::symbol, typename E::string, S(".")>
                >::type
            >::type
            left;
public:
    typedef String::concat<left, typename DefaultUnitStringImpl<UnitSystem<Us...>, Dimension<Es...>>::string> string;
};

template <typename U, typename E>
class DefaultUnitStringImpl<UnitSystem<U>, Dimension<E>>
{
public:
    typedef String::concat<typename U::symbol, typename E::string> string;
};

template <typename T1, typename T2> using DefaultUnitString = typename DefaultUnitStringImpl<T1, T2>::string;





template <typename... Us>
class UnitSystem
{
public:


    static void print(void)
    {
        std::cout << "{";
        (void)std::initializer_list<int> { (Us::printSymbol(), std::cout << ",", 0)... };
        std::cout << "\b}";
    }

    static const int size = length<Us...>::ans;

    typedef UnitSystem<Us...> This;

    template <unsigned int i>
    using baseUnit = Unit<This, SingleDimension<i, size>, Int<1>, typename get<i, Us...>::type::symbol>;



    template <typename, typename, typename> class ProductImpl;
    template <typename, typename, typename> class DivisionImpl;
    template <typename, typename, typename> class PowerImpl;

    template <typename D1, typename D2,
            typename R1, typename R2,
            typename S1, typename S2,
            typename NewSymb>
    class ProductImpl<Unit<This, D1, R1, S1>, Unit<This, D2, R2, S2>, NewSymb>
    {
    public:
        typedef Unit<This, DimensionProduct<D1, D2>, FractionProd<R1,R2>, NewSymb> unit;
    };


    template <typename D1, typename D2,
            typename R1, typename R2,
            typename S1, typename S2,
            typename NewSymb>
    class DivisionImpl<Unit<This, D1, R1, S1>, Unit<This, D2, R2, S2>, NewSymb>
    {
    public:
        typedef Unit<This, DimensionDivision<D1, D2>, FractionDiv<R1,R2>, NewSymb> unit;
    };


    template <typename D1,
            typename R1,
            typename S1,
            typename f,
            typename NewSymb>
    class PowerImpl<Unit<This, D1, R1, S1>, f, NewSymb>
    {
    public:
        typedef Unit<This, DimensionPower<D1, f>, R1, NewSymb> unit;
    };




    template <typename U1, typename U2, typename S = DefaultUnitString<This, DimensionProduct<typename U1::dim, typename U2::dim>>>
        using Product  = typename ProductImpl<U1, U2, S>::unit;

    template <typename U1, typename U2, typename S = DefaultUnitString<This, DimensionDivision<typename U1::dim, typename U2::dim>>>
        using Division = typename DivisionImpl<U1, U2, S>::unit;

    template <typename U1, typename f, typename S = DefaultUnitString<This, DimensionPower<typename U1::dim, f>>>
        using Power    = typename PowerImpl<U1, f, S>::unit;



};
