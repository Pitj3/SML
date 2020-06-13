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

TEST_CASE("fvec2 tests", "[vec2]") {
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

TEST_CASE("dvec2 tests", "[vec2]") {
    sml::dvec2 vec = sml::dvec2(1.0, 0.0);

    REQUIRE(vec != sml::dvec2(0.0, 1.0));
    REQUIRE(vec == sml::dvec2(1.0, 0.0));

    vec = sml::dvec2(1, 20);

    REQUIRE(vec == sml::dvec2(1, 20));

    vec += sml::dvec2(10, 1);

    REQUIRE(vec == sml::dvec2(11, 21));

    vec -= sml::dvec2(10, 1);

    REQUIRE(vec == sml::dvec2(1, 20));

    vec *= sml::dvec2(2, 3);

    REQUIRE(vec == sml::dvec2(2, 60));

    vec *= 2.0;

    REQUIRE(vec == sml::dvec2(4, 120));

    vec /= sml::dvec2(2, 3);

    REQUIRE(vec == sml::dvec2(2, 40));

    vec /= 2.0;

    REQUIRE(vec == sml::dvec2(1, 20));
}

TEST_CASE("fvec3 tests", "[vec3]") {
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

TEST_CASE("dvec3 tests", "[vec3]") {
    sml::dvec3 vec = sml::dvec3(1.0, 0.0, 2.0);

    REQUIRE(vec != sml::dvec3(0.0, 1.0, 3.0));
    REQUIRE(vec == sml::dvec3(1.0, 0.0, 2.0));

    vec = sml::dvec3(1, 20, 5);

    REQUIRE(vec == sml::dvec3(1, 20, 5));

    vec += sml::dvec3(10, 1, 2);

    REQUIRE(vec == sml::dvec3(11, 21, 7));

    vec -= sml::dvec3(10, 1, 2);

    REQUIRE(vec == sml::dvec3(1, 20, 5));

    vec *= sml::dvec3(2, 3, 2);

    REQUIRE(vec == sml::dvec3(2, 60, 10));

    vec *= 2.0;

    REQUIRE(vec == sml::dvec3(4, 120, 20));

    vec /= sml::dvec3(2, 3, 2);

    REQUIRE(vec == sml::dvec3(2, 40, 10));

    vec /= 2.0;

    REQUIRE(vec == sml::dvec3(1, 20, 5));
}

TEST_CASE("fvec4 tests", "[vec4]") {
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

TEST_CASE("dvec4 tests", "[vec4]") {
    sml::dvec4 vec = sml::dvec4(1.0, 0.0, 2.0, 10.0);

    REQUIRE(vec != sml::dvec4(0.0, 1.0, 3.0, 5.0));
    REQUIRE(vec == sml::dvec4(1.0, 0.0, 2.0, 10.0));

    vec = sml::dvec4(1, 20, 5, 20);

    REQUIRE(vec == sml::dvec4(1, 20, 5, 20));

    vec += sml::dvec4(10, 1, 2, 2);

    REQUIRE(vec == sml::dvec4(11, 21, 7, 22));

    vec -= sml::dvec4(10, 1, 2, 2);

    REQUIRE(vec == sml::dvec4(1, 20, 5, 20));
    vec *= sml::dvec4(2, 3, 2, 2);

    REQUIRE(vec == sml::dvec4(2, 60, 10, 40));

    vec *= 2.0;

    REQUIRE(vec == sml::dvec4(4, 120, 20, 80));

    vec /= sml::dvec4(2, 3, 2, 2);

    REQUIRE(vec == sml::dvec4(2, 40, 10, 40));

    vec /= 2.0;

    REQUIRE(vec == sml::dvec4(1, 20, 5, 20));
}

TEST_CASE("fmat2 tests", "[mat2]") {
    sml::fmat2 mat(2, 5, 7, 2);
    sml::fmat2 mat2(6, 2, 5, 1);

    sml::fmat2 res = mat * mat2;
    sml::fmat2 cmp(26, 34, 17, 27);

    sml::fmat2 tp(2, 7, 5, 2);

    REQUIRE(res == cmp);

    REQUIRE(mat.transposed() == tp);

    mat = sml::fmat2(5, 3, 5, 2);
    sml::fvec2 vec(4, 3);

    sml::fvec2 res2 = mat * vec;
    sml::fvec2 cmp2(35, 18);

    REQUIRE(res2 == cmp2);

    mat = sml::fmat2(4, 2, 5, 3);
    sml::fmat2 inv(3.0f/2.0f, -1.0, -5.0f/2.0f, 2.0);

    REQUIRE(mat.inverted() == inv);

    cmp = sml::fmat2(-4, -2, -5, -3);

    REQUIRE(mat.negate() == cmp);
}

TEST_CASE("dmat2 tests", "[mat2]") {
    sml::dmat2 mat(2, 5, 7, 2);
    sml::dmat2 mat2(6, 2, 5, 1);

    sml::dmat2 res = mat * mat2;
    sml::dmat2 cmp(26, 34, 17, 27);

    sml::dmat2 tp(2, 7, 5, 2);

    REQUIRE(res == cmp);

    REQUIRE(mat.transposed() == tp);

    mat = sml::dmat2(5, 3, 5, 2);
    sml::dvec2 vec(4, 3);

    sml::dvec2 res2 = mat * vec;
    sml::dvec2 cmp2(35, 18);

    REQUIRE(res2 == cmp2);

    mat = sml::dmat2(4, 2, 5, 3);
    sml::dmat2 inv(3.0/2.0, -1.0, -5.0/2.0, 2.0);

    REQUIRE(mat.inverted() == inv);

    cmp = sml::dmat2(-4, -2, -5, -3);

    REQUIRE(mat.negate() == cmp);
}

TEST_CASE("fmat3 tests", "[mat3]") {
    sml::fmat3 mat(2, 4, 7, 3, 4, 8, 1, 3, 8);
    sml::fmat3 mat2(1, 6, 3, 4, 7, 5, 7, 8, 3);

    sml::fmat3 tp(2, 3, 1, 4, 4, 3, 7, 8, 8);

    sml::fmat3 res = mat * mat2;
    sml::fmat3 cmp(23, 37, 79, 34, 59, 124, 41, 69, 137);

    REQUIRE(res == cmp);

    REQUIRE(mat.transposed() == tp);

    mat = sml::fmat3(5, 3, 5, 2, 5, 4, 7, 5, 3);
    sml::fvec3 vec(4, 3, 2);

    sml::fvec3 res2 = mat * vec;
    sml::fvec3 cmp2(40, 37, 38);

    REQUIRE(res2 == cmp2);

    cmp.set(5.0f / 84.0f, -4.0f / 21.0f, 13.0f / 84.0f, -11.0f / 42.0f, 5.0f / 21.0f, 5.0f / 42.0f, 25.0f / 84.0f, 1.0f / 21.0f, -19.0f / 84.0f);

    REQUIRE(mat.inverted() == cmp);
}

TEST_CASE("dmat3 tests", "[mat3]") {
    sml::dmat3 mat(2, 4, 7, 3, 4, 8, 1, 3, 8);
    sml::dmat3 mat2(1, 6, 3, 4, 7, 5, 7, 8, 3);

    sml::dmat3 tp(2, 3, 1, 4, 4, 3, 7, 8, 8);

    sml::dmat3 res = mat * mat2;
    sml::dmat3 cmp(23, 37, 79, 34, 59, 124, 41, 69, 137);

    REQUIRE(res == cmp);

    REQUIRE(mat.transposed() == tp);

    mat = sml::dmat3(5, 3, 5, 2, 5, 4, 7, 5, 3);
    sml::dvec3 vec(4, 3, 2);

    sml::dvec3 res2 = mat * vec;
    sml::dvec3 cmp2(40, 37, 38);

    REQUIRE(res2 == cmp2);

    cmp.set(5.0 / 84.0, -4.0 / 21.0, 13.0 / 84.0, -11.0 / 42.0, 5.0 / 21.0, 5.0 / 42.0, 25.0 / 84.0, 1.0 / 21.0, -19.0 / 84.0);

    REQUIRE(mat.inverted() == cmp);
}

TEST_CASE("fmat4 tests", "[mat4]") {
    sml::fmat4 mat(2, 4, 7, 3, 4, 8, 1, 3, 8, 5, 4, 3, 2, 3, 4, 5);
    sml::fmat4 mat2(1, 6, 3, 4, 7, 5, 7, 8, 3, 5, 4, 3, 2, 3, 4, 5);

    sml::fmat4 tp(2, 4, 7, 3, 4, 8, 1, 3, 8, 5, 4, 3, 2, 3, 4, 5);

    sml::fmat4 res = mat * mat2;
    sml::fmat4 cmp(58, 79, 41, 50, 106, 127, 114, 97, 64, 81, 54, 51, 58, 67, 53, 52);

    REQUIRE(res == cmp);

    REQUIRE(mat.transposed() == tp);

    mat = sml::fmat4(5, 3, 5, 2, 5, 4, 7, 5, 3, 5, 4, 3, 2, 3, 4, 5);
    sml::fvec4 vec(4, 3, 2, 3);

    sml::fvec4 res2 = mat * vec;
    sml::fvec4 cmp2(47, 43, 61, 44);

    REQUIRE(res2 == cmp2);
}

TEST_CASE("dmat4 tests", "[mat4]") {
    sml::dmat4 mat(2, 4, 7, 3, 
                   4, 8, 1, 3, 
                   8, 5, 4, 3, 
                   2, 3, 4, 5);

    sml::dmat4 mat2(1, 6, 3, 4, 7, 5, 7, 8, 3, 5, 4, 3, 2, 3, 4, 5);

    sml::dmat4 tp(2, 4, 7, 3, 4, 8, 1, 3, 8, 5, 4, 3, 2, 3, 4, 5);

    sml::dmat4 res = mat * mat2;
    sml::dmat4 cmp(58, 79, 41, 50, 106, 127, 114, 97, 64, 81, 54, 51, 58, 67, 53, 52);

    REQUIRE(res == cmp);

    REQUIRE(mat.transposed() == tp);

    mat = sml::dmat4(5, 3, 5, 2, 5, 4, 7, 5, 3, 5, 4, 3, 2, 3, 4, 5);
    sml::dvec4 vec(4, 3, 2, 3);

    sml::dvec4 res2 = mat * vec;
    sml::dvec4 cmp2(47, 43, 61, 44);

    REQUIRE(res2 == cmp2);
}