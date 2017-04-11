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
class manufactured_solution : public Expression
{
public:
    void eval(Array<double>& values, const Array<double>& x) const
    {
        values[0] = 1 + x[0]*x[0] + x[1]*x[1];
    }
};

//TEST_CASE("Positive p", "[niaou]"){
//    double a;
//    a = 5;
//    REQUIRE(a<5);
//}

TEST_CASE("Checking input is as assigned"){
    create_problem prob;
    double no_elements = 32;
    double u0 = 3.0;
    double f = -4;
    double p = 0;
    prob.set_values (no_elements, u0, f, p);
    REQUIRE(prob.f_input == f);
    REQUIRE(prob.no_elements == no_elements);
    REQUIRE(prob.u0_input == u0);
    REQUIRE(prob.p_input == p);
}

TEST_CASE("Manufactured Soln", "[sd]"){
    create_problem prob;
    double no_elements = 32;
    double u0 = 3.0;
    double f = -4;
    double p = 0;
    prob.set_values (no_elements, u0, f, p);
    prob.problem_solver();
    
    auto mesh = std::make_shared<UnitSquareMesh>(no_elements, no_elements);
    auto V = std::make_shared<pLaplace::FunctionSpace>(mesh);
    auto u_exact = Function(V);
    manufactured_solution ui;
    u_exact.interpolate(ui);
    REQUIRE(no_elements >0);
//double uerror = norm(u_exact,std::string norm_type = "l2");
    
}
