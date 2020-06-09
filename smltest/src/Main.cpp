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

TEST_CASE("vec2 tests", "[vec2]") {
    sml::fvec2 vec = sml::fvec2(1.0f, 0.0f);

    REQUIRE(vec != sml::fvec2(0.0f, 1.0f));
    REQUIRE(vec == sml::fvec2(1.0f, 0.0f));

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 0.0f);

    vec = sml::fvec2(1, 20);

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 20.0f);

    vec += sml::fvec2(10, 1);

    REQUIRE(vec.x == 11.0f);
    REQUIRE(vec.y == 21.0f);

    vec -= sml::fvec2(10, 1);

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 20.0f);

    vec *= sml::fvec2(2, 3);

    REQUIRE(vec.x == 2.0f);
    REQUIRE(vec.y == 60.0f);

    vec *= 2.0f;

    REQUIRE(vec.x == 4.0f);
    REQUIRE(vec.y == 120.0f);

    vec /= sml::fvec2(2, 3);

    REQUIRE(vec.x == 2.0f);
    REQUIRE(vec.y == 40.0f);

    vec /= 2.0f;

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 20.0f);
}

TEST_CASE("vec3 tests", "[vec3]") {
    sml::fvec3 vec = sml::fvec3(1.0f, 0.0f, 2.0f);

    REQUIRE(vec != sml::fvec3(0.0f, 1.0f, 3.0f));
    REQUIRE(vec == sml::fvec3(1.0f, 0.0f, 2.0f));

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 0.0f);
    REQUIRE(vec.z == 2.0f);

    vec = sml::fvec3(1, 20, 5);

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 20.0f);
    REQUIRE(vec.z == 5.0f);

    vec += sml::fvec3(10, 1, 2);

    REQUIRE(vec.x == 11.0f);
    REQUIRE(vec.y == 21.0f);
    REQUIRE(vec.z == 7.0f);

    vec -= sml::fvec3(10, 1, 2);

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 20.0f);
    REQUIRE(vec.z == 5.0f);

    vec *= sml::fvec3(2, 3, 2);

    REQUIRE(vec.x == 2.0f);
    REQUIRE(vec.y == 60.0f);
    REQUIRE(vec.z == 10.0f);

    vec *= 2.0f;

    REQUIRE(vec.x == 4.0f);
    REQUIRE(vec.y == 120.0f);
    REQUIRE(vec.z == 20.0f);

    vec /= sml::fvec3(2, 3, 2);

    REQUIRE(vec.x == 2.0f);
    REQUIRE(vec.y == 40.0f);
    REQUIRE(vec.z == 10.0f);

    vec /= 2.0f;

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 20.0f);
    REQUIRE(vec.z == 5.0f);
}

TEST_CASE("vec4 tests", "[vec4]") {
    sml::fvec4 vec = sml::fvec4(1.0f, 0.0f, 2.0f, 10.0f);

    REQUIRE(vec != sml::fvec4(0.0f, 1.0f, 3.0f, 5.0f));
    REQUIRE(vec == sml::fvec4(1.0f, 0.0f, 2.0f, 10.0f));

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 0.0f);
    REQUIRE(vec.z == 2.0f);
    REQUIRE(vec.w == 10.0f);

    vec = sml::fvec4(1, 20, 5, 20);

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 20.0f);
    REQUIRE(vec.z == 5.0f);
    REQUIRE(vec.w == 20.0f);

    vec += sml::fvec4(10, 1, 2, 2);

    REQUIRE(vec.x == 11.0f);
    REQUIRE(vec.y == 21.0f);
    REQUIRE(vec.z == 7.0f);
    REQUIRE(vec.w == 22.0f);

    vec -= sml::fvec4(10, 1, 2, 2);

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 20.0f);
    REQUIRE(vec.z == 5.0f);
    REQUIRE(vec.w == 20.0f);

    vec *= sml::fvec4(2, 3, 2, 2);

    REQUIRE(vec.x == 2.0f);
    REQUIRE(vec.y == 60.0f);
    REQUIRE(vec.z == 10.0f);
    REQUIRE(vec.w == 40.0f);

    vec *= 2.0f;

    REQUIRE(vec.x == 4.0f);
    REQUIRE(vec.y == 120.0f);
    REQUIRE(vec.z == 20.0f);
    REQUIRE(vec.w == 80.0f);

    vec /= sml::fvec4(2, 3, 2, 2);

    REQUIRE(vec.x == 2.0f);
    REQUIRE(vec.y == 40.0f);
    REQUIRE(vec.z == 10.0f);
    REQUIRE(vec.w == 40.0f);

    vec /= 2.0f;

    REQUIRE(vec.x == 1.0f);
    REQUIRE(vec.y == 20.0f);
    REQUIRE(vec.z == 5.0f);
    REQUIRE(vec.w == 20.0f);
}