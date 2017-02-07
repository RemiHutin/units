#pragma once

#include "string.h"

template <long long a, long long b>
class Gcd
{
public:
    static long long const ans = Gcd<b,a%b>::ans;
}; 


template <long long a>
class Gcd<a, 0>
{
public:
    static long long const ans = a;
};

template <long long a>
class Sign
{
public:
    static long long const ans = (a >= 0) ? 1 : -1;
};

template <long long a>
class Abs
{
public:
    static long long const ans = (a >= 0) ? a : -a;
};

template <typename A, typename B>
class Equals
{
public:
    static bool const ans = false;
};

template <typename A>
class Equals<A,A>
{
public:
    static bool const ans = true;
};


template <long long N, long long D = 1>
class Fraction
{
    static_assert(D != 0, "Error: Invalid fraction");

private:
    static long long const gcd = Gcd<N,D>::ans;
public:
    static long long const num = N/gcd;
    static long long const den = D/gcd;

    typedef typename std::conditional
                     <
                        den == 1,
                        String::fromInt<num>,
                        String::concat3<String::fromInt<num>, S("/"), String::fromInt<den>>
                     >::type string;

    static void print(void)
    {
        string::print();
    }

    static double value(void)
    {
        return (double)N / D;
    }

};



template <long long d> using Int =  Fraction<d,1>;

template <typename f1, typename f2>
class FractionSum_impl
{
public:
    typedef Fraction<f1::num * f2::den + f2::num * f1::den, f1::den * f2::den> ans;
};

template <typename f1, typename f2>
class FractionSub_impl
{
public:
    typedef Fraction<f1::num * f2::den - f2::num * f1::den, f1::den * f2::den> ans;
};

template <typename f1, typename f2>
class FractionProd_impl
{
public:
    typedef Fraction<f1::num * f2::num, f1::den * f2::den> ans;
};

template <typename f1, typename f2>
class FractionDiv_impl
{
public:
    typedef Fraction<f1::num * f2::den, f1::den * f2::num> ans;
};

template <typename f, int p>
class FractionPower_impl
{
public:
    typedef Fraction<(p>=0)?f::num:f::den, (p>=0)?f::den:f::num> f2; // if p >= 0 then f2 = f else f2 = 1/f
    typedef typename FractionProd_impl<typename FractionPower_impl<f2, p*Sign<p>::ans-1>::ans, f2>::ans ans;
};

template <typename f>
class FractionPower_impl<f, 0>
{
public:
    typedef Int<1> ans;
};

template <typename f1, typename f2> using FractionSum       = typename FractionSum_impl   <f1, f2>::ans;
template <typename f1, typename f2> using FractionSub       = typename FractionSub_impl   <f1, f2>::ans;
template <typename f1, typename f2> using FractionProd      = typename FractionProd_impl  <f1, f2>::ans;
template <typename f1, typename f2> using FractionDiv       = typename FractionDiv_impl   <f1, f2>::ans;
template <typename f1, int p>       using FractionPower     = typename FractionPower_impl <f1, p>::ans;
template <typename f1>              using FractionSquare    = typename FractionPower_impl <f1, 2>::ans;
template <typename f1>              using FractionInverse   = typename FractionPower_impl <f1, -1>::ans;
