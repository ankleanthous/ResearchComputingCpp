#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <dolfin.h>
#include <iostream>
#include "../Code/pLaplace.h"
#include "../Code/problem_classes.h"

using namespace dolfin;

TEST_CASE("Checking input is as assigned"){
    create_problem prob;
    double no_elements = 32;
    double u0 = 3.0;
    double f = -4;
    double p = 3;
    prob.set_values (no_elements, u0, f, p);
    REQUIRE(prob.f_input == f);
    REQUIRE(prob.no_elements == no_elements);
    REQUIRE(prob.u0_input == u0);
    REQUIRE(prob.p_input == p);
}

TEST_CASE("Check p is greater than 2"){
    create_problem prob;
    double no_elements = 32;
    double u0 = 3.0;
    double f = -4;
    double p = -2;
    prob.set_values (no_elements, u0, f, p);
    REQUIRE( prob.p_input >2);
}

TEST_CASE("Check type of input is correct"){
    create_problem prob;
    REQUIRE_THROWS(prob.set_values(1,1,2,1)); //this should fail as p<2
    REQUIRE_THROWS(prob.set_values(-1,1,2,3)); //this should fail as no_elements<0
}

