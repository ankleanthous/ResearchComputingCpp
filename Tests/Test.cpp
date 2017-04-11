#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <dolfin.h>
#include <iostream>
#include "../Code/pLaplace.h"
#include "../Code/problem_classes.h"

using namespace dolfin;

//unsigned int Factorial( unsigned int number ) {
//    return number <= 1 ? number : Factorial(number-1)*number;
//}
//
//TEST_CASE( "Factorials are computed", "[factorial]" ) {
//    REQUIRE( Factorial(1) == 1 );
//    REQUIRE( Factorial(2) == 2 );
//    REQUIRE( Factorial(3) == 6 );
//    REQUIRE( Factorial(10) == 3628800 );
//}

//TEST_CASE("Area","[xxx]"){
//    Rectangle rect;
//    rect.set_values (3,4);
//    REQUIRE(rect.area() == 12);
//}


TEST_CASE("Positive p", "[niaou]"){
    double a;
    a = 5;
    REQUIRE(a<5);
}
