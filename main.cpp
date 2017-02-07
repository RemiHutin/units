#include <iostream>
#include <typeinfo>
#include "unit.h"
#include "fraction.h"
#include "string.h"
#include "unitsystem.h"


typedef BaseUnit<S("kg")> _Kilogram_;
typedef BaseUnit<S("m")> _Metre_;
typedef BaseUnit<S("s")> _Second_;

typedef UnitSystem<_Kilogram_, _Metre_, _Second_> MLT;


typedef MLT::baseUnit<0> Kilogram;
typedef MLT::baseUnit<1> Metre;
typedef MLT::baseUnit<2> Second;

typedef Unit<MLT, Dimension<Int<0>, Int<1>, Int<0>>, Int<1000>, S("km")> Kilometre;

typedef MLT::Division<Metre, Second> MetrePerSecond;




typedef Dimension<Int<0>, Int<1>, Int<0>> D1;
typedef Dimension<Int<0>, Int<1>, Int<-1>> D2;







int main(void)
{
    Metre q(42.0);

    std::cout << q << std::endl;


    Kilometre l1(20.0);
    Second l2(10.0)
    MetrePerSecond plop;

    plop = l1/l2;

    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;

    //l2 = l1;




    std::cout << plop << std::endl;

    return 0;

















    /*


    DefaultUnitString<MLT, D2>::print();

    std::cout << std::endl;

    String::fromInt<-130/7>::print();

    std::cout << std::endl;

    Fraction<38,-2>::string::print();

    std::cout << std::endl;
    S("AZE")::print();
    MetrePerSecond::printSystem();
    std::cout << std::endl;

    D1::print();
    D2::print();


    DimensionProduct<D1, D2>::print();

    MetrePerSecond test = 3.7;

    test.print();

    //Length length = 1._m;
    //Length length = 1 * meter;

    //Length::unit<Meter> length = 3._m;
    //Length::unit<Kilometer> length = 3._m;

    //Quantity<Metre> q;
    std::cout << std::endl;

    Metre::dim::print();
    Second::dim::print();
    MetrePerSecond::printSymbol();


    DimensionSqrt<SingleDimension<2, 5>>::print();

    std::cout << std::endl;
    FractionInverse<Fraction<2,5>>::print();
    std::cout << std::endl;

    Fraction<2,4>::print();
    FractionSum< Fraction<1,2>, Fraction<1,3>>::print();
    */
    return 0;
}
