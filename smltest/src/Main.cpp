#include <stdio.h>
#include <sml.h>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Sin is computed", "[sin]") {
    REQUIRE(sml::sin(constants::pi) == std::sin(constants::pi));
}

TEST_CASE("Cos is computed", "[cos]") {
    REQUIRE(sml::cos(constants::pi) == std::cos(constants::pi));
}

TEST_CASE("Tan is computed", "[tan]") {
    REQUIRE(sml::tan(constants::pi) == std::tan(constants::pi));
}

TEST_CASE("Abs is computed", "[abs]") {
    REQUIRE(sml::abs(1.53f) == std::abs(1.53f));
    REQUIRE(sml::abs(-1.6354f) == std::abs(-1.6354f));
    REQUIRE(sml::abs(1.578643565564356) == std::abs(1.578643565564356));
    REQUIRE(sml::abs(-156.394756394674) == std::abs(-156.394756394674));
}