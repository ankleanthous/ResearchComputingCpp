#include "catch.hpp"

TEST_CASE("My first test","[some group identifier]"){
	int a = 5;
	REQUIRE(a<6);
}