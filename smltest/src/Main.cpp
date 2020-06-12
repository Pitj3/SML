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

    vec = sml::fvec2(1, 20);

    REQUIRE(vec == sml::fvec2(1, 20));

    vec += sml::fvec2(10, 1);

    REQUIRE(vec == sml::fvec2(11, 21));

    vec -= sml::fvec2(10, 1);

    REQUIRE(vec == sml::fvec2(1, 20));

    vec *= sml::fvec2(2, 3);

    REQUIRE(vec == sml::fvec2(2, 60));

    vec *= 2.0f;

    REQUIRE(vec == sml::fvec2(4, 120));

    vec /= sml::fvec2(2, 3);

    REQUIRE(vec == sml::fvec2(2, 40));

    vec /= 2.0f;

    REQUIRE(vec == sml::fvec2(1, 20));
}

TEST_CASE("vec3 tests", "[vec3]") {
    sml::fvec3 vec = sml::fvec3(1.0f, 0.0f, 2.0f);

    REQUIRE(vec != sml::fvec3(0.0f, 1.0f, 3.0f));
    REQUIRE(vec == sml::fvec3(1.0f, 0.0f, 2.0f));

    vec = sml::fvec3(1, 20, 5);

    REQUIRE(vec == sml::fvec3(1, 20, 5));

    vec += sml::fvec3(10, 1, 2);

    REQUIRE(vec == sml::fvec3(11, 21, 7));

    vec -= sml::fvec3(10, 1, 2);

    REQUIRE(vec == sml::fvec3(1, 20, 5));

    vec *= sml::fvec3(2, 3, 2);

    REQUIRE(vec == sml::fvec3(2, 60, 10));

    vec *= 2.0f;

    REQUIRE(vec == sml::fvec3(4, 120, 20));

    vec /= sml::fvec3(2, 3, 2);

    REQUIRE(vec == sml::fvec3(2, 40, 10));

    vec /= 2.0f;

    REQUIRE(vec == sml::fvec3(1, 20, 5));
}

TEST_CASE("vec4 tests", "[vec4]") {
    sml::fvec4 vec = sml::fvec4(1.0f, 0.0f, 2.0f, 10.0f);

    REQUIRE(vec != sml::fvec4(0.0f, 1.0f, 3.0f, 5.0f));
    REQUIRE(vec == sml::fvec4(1.0f, 0.0f, 2.0f, 10.0f));

    vec = sml::fvec4(1, 20, 5, 20);

    REQUIRE(vec == sml::fvec4(1, 20, 5, 20));

    vec += sml::fvec4(10, 1, 2, 2);

    REQUIRE(vec == sml::fvec4(11, 21, 7, 22));

    vec -= sml::fvec4(10, 1, 2, 2);

    REQUIRE(vec == sml::fvec4(1, 20, 5, 20));
    vec *= sml::fvec4(2, 3, 2, 2);

    REQUIRE(vec == sml::fvec4(2, 60, 10, 40));

    vec *= 2.0f;

    REQUIRE(vec == sml::fvec4(4, 120, 20, 80));

    vec /= sml::fvec4(2, 3, 2, 2);

    REQUIRE(vec == sml::fvec4(2, 40, 10, 40));

    vec /= 2.0f;

    REQUIRE(vec == sml::fvec4(1, 20, 5, 20));
}

TEST_CASE("fmat2 tests", "[mat2]") {
    sml::fmat2 mat(2, 5, 7, 2);
    sml::fmat2 mat2(6, 2, 5, 1);

    sml::fmat2 res = mat * mat2;
    sml::fmat2 cmp(26, 34, 17, 27);

    REQUIRE(res == cmp);

    mat = sml::fmat2(5, 3, 5, 2);
    sml::fvec2 vec(4, 3);

    sml::fvec2 res2 = mat * vec;
    sml::fvec2 cmp2(35, 18);

    REQUIRE(res2 == cmp2);

    mat = sml::fmat2(4, 2, 5, 3);
    sml::fmat2 inv(3.0f/2.0f, -1.0, -5.0f/2.0f, 2.0);

    REQUIRE(mat.inverted() == inv);

    sml::fmat2 tp(4, 5, 2, 3);

    REQUIRE(mat == tp);

    cmp = sml::fmat2(-4, -2, -5, -3);

    REQUIRE(mat.negate() == cmp);
}

TEST_CASE("dmat2 tests", "[mat2]") {
    sml::dmat2 mat(2, 5, 7, 2);
    sml::dmat2 mat2(6, 2, 5, 1);

    sml::dmat2 res = mat * mat2;
    sml::dmat2 cmp(26, 34, 17, 27);

    REQUIRE(res == cmp);

    mat = sml::dmat2(5, 3, 5, 2);
    sml::dvec2 vec(4, 3);

    sml::dvec2 res2 = mat * vec;
    sml::dvec2 cmp2(35, 18);

    REQUIRE(res2 == cmp2);

    mat = sml::dmat2(4, 2, 5, 3);
    sml::dmat2 inv(3.0/2.0, -1.0, -5.0/2.0, 2.0);

    REQUIRE(mat.inverted() == inv);

    sml::dmat2 tp(4, 5, 2, 3);

    REQUIRE(mat == tp);

    cmp = sml::dmat2(-4, -2, -5, -3);

    REQUIRE(mat.negate() == cmp);
}

TEST_CASE("fmat3 tests", "[mat3]") {
    sml::fmat3 mat(2, 4, 7, 3, 4, 8, 1, 3, 8);
    sml::fmat3 mat2(1, 6, 3, 4, 7, 5, 7, 8, 3);

    sml::fmat3 res = mat * mat2;
    sml::fmat3 cmp(23, 37, 79, 34, 59, 124, 41, 69, 137);

    REQUIRE(res == cmp);

    mat = sml::fmat3(5, 3, 5, 2, 5, 4, 7, 5, 3);
    sml::fvec3 vec(4, 3, 2);

    sml::fvec3 res2 = mat * vec;
    sml::fvec3 cmp2(40, 37, 38);

    REQUIRE(res2 == cmp2);
}