#pragma once

namespace String
{

    template<char C, char... Cs>
    class impl
    {
    public:
        static void print(void)
        {
            std::cout << C;
            impl<Cs...>::print();
        }
        
    };


    template<char C>
    class impl<C>
    {
    public:
        static void print(void)
        {
            std::cout << C;
        }
    };


    template< std::size_t N, std::size_t M >
    constexpr char at(const char(&c)[ M ]) noexcept
    {
        static_assert(M < 100, "String too long");
        return (N < M) ? c[N] : 0;
    }
    
    
    template <typename>
    class toLiteral
    {
    public:
        static char string[100];
    };
    
    

    
    namespace Impl
    {
        template<typename, char ...>
        class make;

        template<typename T>
        class make<T>
        {
        public:
            using type = T;
        };

        template<char... C1s, char C, char... C2s>
        class make<impl<C1s...>, C, C2s...>
            : public std::conditional<C == '\0',
                make<impl<C1s... >>,
                make<impl<C1s..., C>, C2s...>>::type
        {};

        
        

        template <typename T1, typename T2>
        class concat;

        template<char... C1s, char... C2s>
        class concat<impl<C1s...>, impl<C2s...>>
        {
        public:
            typedef impl<C1s..., C2s... > type;
        };
        
        
        template <typename T1, typename T2, typename T3>
        class concat3;

        template<char... C1s, char... C2s, char... C3s>
        class concat3<impl<C1s...>, impl<C2s...>, impl<C3s...>>
        {
        public:
            typedef impl<C1s..., C2s..., C3s...> type;
        };
        


        template <long long N>
        class fromIntAux
        {
        public:
            typedef typename std::conditional
                    <
                        N >= 0,
                        typename make
                        <
                            typename fromIntAux<N/10>::type, 
                            N%10 + '0'
                        >::type,
                        typename concat
                        <
                            impl<'-'>,
                            typename make
                            <
                                typename fromIntAux<-N/10>::type, 
                                -N%10 + '0'
                            >::type
                        >::type
                    >::type
                    type;
        };

        template <>
        class fromIntAux<0>
        {
        public:
            typedef impl<'\0'> type;
        };
        
        
        
        template <long long N>
        class fromInt
        {
        public:
            typedef typename fromIntAux<N>::type type;
        };
        
        template <>
        class fromInt<0>
        {
        public:
            typedef impl<'0'> type;
        };
    }
    
    

    template<typename T, char... Cs>                    using make = typename Impl::make<T, Cs...>::type;
    template <typename T1, typename T2>                 using concat = typename Impl::concat<T1, T2>::type;
    template <typename T1, typename T2, typename T3>    using concat3 = typename Impl::concat3<T1, T2, T3>::type;
    template <long long N>                              using fromInt = typename Impl::fromInt<N>::type;
}


#define INTERNAL_STRING(n,x) \
   String::at<n##0>(x),      \
   String::at<n##1>(x),      \
   String::at<n##2>(x),      \
   String::at<n##3>(x),      \
   String::at<n##4>(x),      \
   String::at<n##5>(x),      \
   String::at<n##6>(x),      \
   String::at<n##7>(x),      \
   String::at<n##8>(x),      \
   String::at<n##9>(x)

#define S(x)                      \
   String::make<String::impl<'\0'>,    \
          INTERNAL_STRING(,x),         \
          INTERNAL_STRING(1,x),        \
          INTERNAL_STRING(2,x),        \
          INTERNAL_STRING(3,x),        \
          INTERNAL_STRING(4,x),        \
          INTERNAL_STRING(5,x),        \
          INTERNAL_STRING(6,x),        \
          INTERNAL_STRING(7,x),        \
          INTERNAL_STRING(8,x),        \
          INTERNAL_STRING(9,x) >
          
