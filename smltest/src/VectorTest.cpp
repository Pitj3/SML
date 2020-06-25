#include <vec2.h>

#include <gtest/gtest.h>

using namespace sml;

// FVEC2 TESTS

TEST(fvec2, DefaultConstructor)
{
	fvec2 v;
	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
}

TEST(fvec2, ComponentConstructor)
{
	fvec2 v(10, 15);
	EXPECT_EQ(v.x, 10);
	EXPECT_EQ(v.y, 15);
}

TEST(fvec2, ScalarConstructor)
{
	fvec2 v(2);
	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 2);
}

TEST(fvec2, ArrayConstructor)
{
	f32 values[] = {
		2.0f, 10.0f 
	};

	fvec2 v(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
}

TEST(fvec2, CopyConstructor)
{
	fvec2 orig(5, 10);
	fvec2 v(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
}

TEST(fvec2, MoveConstructor)
{
	fvec2 orig(5, 10);
	fvec2 v = std::move(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
}

TEST(fvec2, CopyAssignment)
{
	fvec2 orig(2, 5);
	fvec2 v;
	v = orig;

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
}

TEST(fvec2, MoveAssignment)
{
	fvec2 orig(2, 5);
	fvec2 v;
	v = std::move(orig);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
}

TEST(fvec2, Zero)
{
	fvec2 v(10, 10);
	v.zero();

	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
}

TEST(fvec2, ComponentSet)
{
	fvec2 v;
	v.set(15, 5);

	EXPECT_EQ(v.x, 15);
	EXPECT_EQ(v.y, 5);
}

TEST(fvec2, ArraySet)
{
	f32 values[] = {
		2.0f, 10.0f
	};

	fvec2 v;
	v.set(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
}

TEST(fvec2, Equals)
{
	fvec2 lhs(10, 15);
	fvec2 rhs(10, 15);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(fvec2, NotEquals)
{
	fvec2 lhs(10, 15);
	fvec2 rhs(10, 10);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(fvec2, VectorPlusEquals)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(5, 2);

	lhs += rhs;

	EXPECT_EQ(lhs.x, 15);
	EXPECT_EQ(lhs.y, 12);
}

TEST(fvec2, VectorMinusEquals)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(5, 2);

	lhs -= rhs;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 8);
}

TEST(fvec2, VectorTimesEquals)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(5, 2);

	lhs *= rhs;

	EXPECT_EQ(lhs.x, 50);
	EXPECT_EQ(lhs.y, 20);
}

TEST(fvec2, ScalarTimesEquals)
{
	fvec2 lhs(10, 10);

	lhs *= 2.0f;

	EXPECT_EQ(lhs.x, 20);
	EXPECT_EQ(lhs.y, 20);
}

TEST(fvec2, VectorDivideEquals)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(5, 2);

	lhs /= rhs;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 5);
}

TEST(fvec2, ScalarDivideEquals)
{
	fvec2 lhs(10, 10);

	lhs /= 2.0f;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 5);
}

TEST(fvec2, Dot)
{
	fvec2 lhs(10, 15);
	fvec2 rhs(5, 5);

	f32 d = lhs.dot(rhs);

	EXPECT_EQ(d, 125);
}

TEST(fvec2, Length)
{
	fvec2 v(15, 20);

	f32 l = v.length();

	EXPECT_EQ(l, 25);
}

TEST(fvec2, LengthSquared)
{
	fvec2 v(15, 20);

	f32 l = v.lengthsquared();

	EXPECT_EQ(l, 625);
}

TEST(fvec2, Normalize)
{
	fvec2 v(10, 15);
	f32 l = v.length();
	v.normalize();

	EXPECT_EQ(v.x, 10 / l);
	EXPECT_EQ(v.y, 15 / l);

	EXPECT_EQ(v.length(), 1);
}

TEST(fvec2, Distance)
{
	fvec2 lhs(0, 0);
	fvec2 rhs(10, 0);

	f32 d = fvec2::distance(lhs, rhs);

	EXPECT_EQ(d, 10);
}

TEST(fvec2, Min)
{
	fvec2 lhs(10, 15);
	fvec2 rhs(4, 25);

	fvec2 m = fvec2::min(lhs, rhs);

	EXPECT_EQ(m.x, 4);
	EXPECT_EQ(m.y, 15);
}

TEST(fvec2, Max)
{
	fvec2 lhs(10, 15);
	fvec2 rhs(4, 25);

	fvec2 m = fvec2::max(lhs, rhs);

	EXPECT_EQ(m.x, 10);
	EXPECT_EQ(m.y, 25);
}

TEST(fvec2, Clamp)
{
	fvec2 min(10, 10);
	fvec2 max(20, 20);
	fvec2 val(25, 5);

	fvec2 c = fvec2::clamp(val, min, max);

	EXPECT_EQ(c.x, 20);
	EXPECT_EQ(c.y, 10);
}

TEST(fvec2, Lerp)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(20, 20);

	fvec2 l = fvec2::lerp(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
}

TEST(fvec2, LerpClamped)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(20, 20);

	fvec2 l = fvec2::lerpclamped(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
}

TEST(fvec2, VectorPlusOperator)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(15, 20);

	fvec2 r = lhs + rhs;

	EXPECT_EQ(r.x, 25);
	EXPECT_EQ(r.y, 30);
}

TEST(fvec2, VectorMinusOperator)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(15, 20);

	fvec2 r = lhs - rhs;

	EXPECT_EQ(r.x, -5);
	EXPECT_EQ(r.y, -10);
}

TEST(fvec2, VectorMultiplyOperator)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(5, 2);

	fvec2 r = lhs * rhs;

	EXPECT_EQ(r.x, 50);
	EXPECT_EQ(r.y, 20);
}

TEST(fvec2, ScalarMultiplyOperator)
{
	fvec2 lhs(10, 10);
	fvec2 r = lhs * 2.0f;

	EXPECT_EQ(r.x, 20);
	EXPECT_EQ(r.y, 20);
}

TEST(fvec2, VectorDivideOperator)
{
	fvec2 lhs(10, 10);
	fvec2 rhs(5, 2);

	fvec2 r = lhs / rhs;

	EXPECT_EQ(r.x, 2);
	EXPECT_EQ(r.y, 5);
}

TEST(fvec2, ScalarDivideOperator)
{
	fvec2 lhs(10, 10);
	fvec2 r = lhs / 2.0f;

	EXPECT_EQ(r.x, 5);
	EXPECT_EQ(r.y, 5);
}

TEST(fvec2, NegateOperator)
{
	fvec2 v(10, 5);
	v = -v;

	EXPECT_EQ(v.x, -10);
	EXPECT_EQ(v.y, -5);
}

// DVEC2 TESTS

TEST(dvec2, DefaultConstructor)
{
	dvec2 v;
	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
}

TEST(dvec2, ComponentConstructor)
{
	dvec2 v(10, 15);
	EXPECT_EQ(v.x, 10);
	EXPECT_EQ(v.y, 15);
}

TEST(dvec2, ScalarConstructor)
{
	dvec2 v(2);
	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 2);
}

TEST(dvec2, ArrayConstructor)
{
	f64 values[] = {
		2.0, 10.0
	};

	dvec2 v(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
}

TEST(dvec2, CopyConstructor)
{
	dvec2 orig(5, 10);
	dvec2 v(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
}

TEST(dvec2, MoveConstructor)
{
	dvec2 orig(5, 10);
	dvec2 v = std::move(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
}

TEST(dvec2, CopyAssignment)
{
	dvec2 orig(2, 5);
	dvec2 v;
	v = orig;

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
}

TEST(dvec2, MoveAssignment)
{
	dvec2 orig(2, 5);
	dvec2 v;
	v = std::move(orig);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
}

TEST(dvec2, Zero)
{
	dvec2 v(10, 10);
	v.zero();

	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
}

TEST(dvec2, ComponentSet)
{
	dvec2 v;
	v.set(15, 5);

	EXPECT_EQ(v.x, 15);
	EXPECT_EQ(v.y, 5);
}

TEST(dvec2, ArraySet)
{
	f64 values[] = {
		2.0, 10.0
	};

	dvec2 v;
	v.set(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
}

TEST(dvec2, Equals)
{
	dvec2 lhs(10, 15);
	dvec2 rhs(10, 15);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(dvec2, NotEquals)
{
	dvec2 lhs(10, 15);
	dvec2 rhs(10, 10);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(dvec2, VectorPlusEquals)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(5, 2);

	lhs += rhs;

	EXPECT_EQ(lhs.x, 15);
	EXPECT_EQ(lhs.y, 12);
}

TEST(dvec2, VectorMinusEquals)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(5, 2);

	lhs -= rhs;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 8);
}

TEST(dvec2, VectorTimesEquals)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(5, 2);

	lhs *= rhs;

	EXPECT_EQ(lhs.x, 50);
	EXPECT_EQ(lhs.y, 20);
}

TEST(dvec2, ScalarTimesEquals)
{
	dvec2 lhs(10, 10);

	lhs *= 2.0;

	EXPECT_EQ(lhs.x, 20);
	EXPECT_EQ(lhs.y, 20);
}

TEST(dvec2, VectorDivideEquals)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(5, 2);

	lhs /= rhs;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 5);
}

TEST(dvec2, ScalarDivideEquals)
{
	dvec2 lhs(10, 10);

	lhs /= 2.0;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 5);
}

TEST(dvec2, Dot)
{
	dvec2 lhs(10, 15);
	dvec2 rhs(5, 5);

	f64 d = lhs.dot(rhs);

	EXPECT_EQ(d, 125);
}

TEST(dvec2, Length)
{
	dvec2 v(15, 20);

	f64 l = v.length();

	EXPECT_EQ(l, 25);
}

TEST(dvec2, LengthSquared)
{
	dvec2 v(15, 20);

	f64 l = v.lengthsquared();

	EXPECT_EQ(l, 625);
}

TEST(dvec2, Normalize)
{
	dvec2 v(10, 15);
	f64 l = v.length();
	v.normalize();

	EXPECT_EQ(v.x, 10 / l);
	EXPECT_EQ(v.y, 15 / l);

	EXPECT_EQ(v.length(), 1);
}

TEST(dvec2, Distance)
{
	dvec2 lhs(0, 0);
	dvec2 rhs(10, 0);

	f64 d = dvec2::distance(lhs, rhs);

	EXPECT_EQ(d, 10);
}

TEST(dvec2, Min)
{
	dvec2 lhs(10, 15);
	dvec2 rhs(4, 25);

	dvec2 m = dvec2::min(lhs, rhs);

	EXPECT_EQ(m.x, 4);
	EXPECT_EQ(m.y, 15);
}

TEST(dvec2, Max)
{
	dvec2 lhs(10, 15);
	dvec2 rhs(4, 25);

	dvec2 m = dvec2::max(lhs, rhs);

	EXPECT_EQ(m.x, 10);
	EXPECT_EQ(m.y, 25);
}

TEST(dvec2, Clamp)
{
	dvec2 min(10, 10);
	dvec2 max(20, 20);
	dvec2 val(25, 5);

	dvec2 c = dvec2::clamp(val, min, max);

	EXPECT_EQ(c.x, 20);
	EXPECT_EQ(c.y, 10);
}

TEST(dvec2, Lerp)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(20, 20);

	dvec2 l = dvec2::lerp(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
}

TEST(dvec2, LerpClamped)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(20, 20);

	dvec2 l = dvec2::lerpclamped(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
}

TEST(dvec2, VectorPlusOperator)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(15, 20);

	dvec2 r = lhs + rhs;

	EXPECT_EQ(r.x, 25);
	EXPECT_EQ(r.y, 30);
}

TEST(dvec2, VectorMinusOperator)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(15, 20);

	dvec2 r = lhs - rhs;

	EXPECT_EQ(r.x, -5);
	EXPECT_EQ(r.y, -10);
}

TEST(dvec2, VectorMultiplyOperator)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(5, 2);

	dvec2 r = lhs * rhs;

	EXPECT_EQ(r.x, 50);
	EXPECT_EQ(r.y, 20);
}

TEST(dvec2, ScalarMultiplyOperator)
{
	dvec2 lhs(10, 10);
	dvec2 r = lhs * 2.0;

	EXPECT_EQ(r.x, 20);
	EXPECT_EQ(r.y, 20);
}

TEST(dvec2, VectorDivideOperator)
{
	dvec2 lhs(10, 10);
	dvec2 rhs(5, 2);

	dvec2 r = lhs / rhs;

	EXPECT_EQ(r.x, 2);
	EXPECT_EQ(r.y, 5);
}

TEST(dvec2, ScalarDivideOperator)
{
	dvec2 lhs(10, 10);
	dvec2 r = lhs / 2.0;

	EXPECT_EQ(r.x, 5);
	EXPECT_EQ(r.y, 5);
}

TEST(dvec2, NegateOperator)
{
	dvec2 v(10, 5);
	v = -v;

	EXPECT_EQ(v.x, -10);
	EXPECT_EQ(v.y, -5);
}

#include "vec3.h"

// FVEC3 TESTS

TEST(fvec3, DefaultConstructor)
{
	fvec3 v;
	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
	EXPECT_EQ(v.z, 0);
}

TEST(fvec3, ComponentConstructor)
{
	fvec3 v(10, 15, 20);
	EXPECT_EQ(v.x, 10);
	EXPECT_EQ(v.y, 15);
	EXPECT_EQ(v.z, 20);
}

TEST(fvec3, ScalarConstructor)
{
	fvec3 v(2);
	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 2);
	EXPECT_EQ(v.z, 2);
}

TEST(fvec3, ArrayConstructor)
{
	f32 values[] = {
		2.0f, 10.0f, 20.0f
	};

	fvec3 v(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 20);
}

TEST(fvec3, CopyConstructor)
{
	fvec3 orig(5, 10, 15);
	fvec3 v(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 15);
}

TEST(fvec3, MoveConstructor)
{
	fvec3 orig(5, 10, 15);
	fvec3 v = std::move(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 15);
}

TEST(fvec3, CopyAssignment)
{
	fvec3 orig(2, 5, 10);
	fvec3 v;
	v = orig;

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 10);
}

TEST(fvec3, MoveAssignment)
{
	fvec3 orig(2, 5, 10);
	fvec3 v;
	v = std::move(orig);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 10);
}

TEST(fvec3, Zero)
{
	fvec3 v(10, 10, 20);
	v.zero();

	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
	EXPECT_EQ(v.z, 0);
}

TEST(fvec3, ComponentSet)
{
	fvec3 v;
	v.set(15, 5, 2);

	EXPECT_EQ(v.x, 15);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 2);
}

TEST(fvec3, ArraySet)
{
	f32 values[] = {
		2.0f, 10.0f, 20.0f
	};

	fvec3 v;
	v.set(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 20);
}

TEST(fvec3, Equals)
{
	fvec3 lhs(10, 15, 20);
	fvec3 rhs(10, 15, 20);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(fvec3, NotEquals)
{
	fvec3 lhs(10, 15, 20);
	fvec3 rhs(10, 10, 5);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(fvec3, VectorPlusEquals)
{
	fvec3 lhs(10, 10, 10);
	fvec3 rhs(5, 2, 5);

	lhs += rhs;

	EXPECT_EQ(lhs.x, 15);
	EXPECT_EQ(lhs.y, 12);
	EXPECT_EQ(lhs.z, 15);
}

TEST(fvec3, VectorMinusEquals)
{
	fvec3 lhs(10, 10, 10);
	fvec3 rhs(5, 2, 5);

	lhs -= rhs;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 8);
	EXPECT_EQ(lhs.z, 5);
}

TEST(fvec3, VectorTimesEquals)
{
	fvec3 lhs(10, 10, 10);
	fvec3 rhs(5, 2, 5);

	lhs *= rhs;

	EXPECT_EQ(lhs.x, 50);
	EXPECT_EQ(lhs.y, 20);
	EXPECT_EQ(lhs.z, 50);
}

TEST(fvec3, ScalarTimesEquals)
{
	fvec3 lhs(10, 10, 10);

	lhs *= 2.0f;

	EXPECT_EQ(lhs.x, 20);
	EXPECT_EQ(lhs.y, 20);
	EXPECT_EQ(lhs.z, 20);
}

TEST(fvec3, VectorDivideEquals)
{
	fvec3 lhs(10, 10, 10);
	fvec3 rhs(5, 2, 5);

	lhs /= rhs;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 5);
	EXPECT_EQ(lhs.z, 2);
}

TEST(fvec3, ScalarDivideEquals)
{
	fvec3 lhs(10, 10, 10);

	lhs /= 2.0f;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 5);
	EXPECT_EQ(lhs.z, 5);
}

TEST(fvec3, Dot)
{
	fvec3 lhs(10, 15, 20);
	fvec3 rhs(5, 5, 5);

	f32 d = lhs.dot(rhs);

	EXPECT_EQ(d, 225);
}

TEST(fvec3, Length)
{
	fvec3 v(15, 20, 25);

	f32 l = v.length();

	EXPECT_EQ(l, sml::sqrt(1250.0f));
}

TEST(fvec3, LengthSquared)
{
	fvec3 v(15, 20, 25);

	f32 l = v.lengthsquared();

	EXPECT_EQ(l, 1250);
}

TEST(fvec3, Normalize)
{
	fvec3 v(10, 15, 10);
	f32 l = v.length();
	v.normalize();

	EXPECT_EQ(v.x, 10 / l);
	EXPECT_EQ(v.y, 15 / l);
	EXPECT_EQ(v.z, 10 / l);

	EXPECT_EQ(v.length(), 1);
}

TEST(fvec3, Distance)
{
	fvec3 lhs(0, 0, 0);
	fvec3 rhs(10, 0, 0);

	f32 d = fvec3::distance(lhs, rhs);

	EXPECT_EQ(d, 10);
}

TEST(fvec3, Min)
{
	fvec3 lhs(10, 15, 20);
	fvec3 rhs(4, 25, 40);

	fvec3 m = fvec3::min(lhs, rhs);

	EXPECT_EQ(m.x, 4);
	EXPECT_EQ(m.y, 15);
	EXPECT_EQ(m.z, 20);
}

TEST(fvec3, Max)
{
	fvec3 lhs(10, 15, 20);
	fvec3 rhs(4, 25, 40);

	fvec3 m = fvec3::max(lhs, rhs);

	EXPECT_EQ(m.x, 10);
	EXPECT_EQ(m.y, 25);
	EXPECT_EQ(m.z, 40);
}

TEST(fvec3, Clamp)
{
	fvec3 min(10, 10, 10);
	fvec3 max(20, 20, 20);
	fvec3 val(25, 5, 14);

	fvec3 c = fvec3::clamp(val, min, max);

	EXPECT_EQ(c.x, 20);
	EXPECT_EQ(c.y, 10);
	EXPECT_EQ(c.z, 14);
}

TEST(fvec3, Lerp)
{
	fvec3 lhs(10, 10, 10);
	fvec3 rhs(20, 20, 20);

	fvec3 l = fvec3::lerp(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
	EXPECT_EQ(l.z, 15);
}

TEST(fvec3, LerpClamped)
{
	fvec3 lhs(10, 10, 10);
	fvec3 rhs(20, 20, 20);

	fvec3 l = fvec3::lerpclamped(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
	EXPECT_EQ(l.z, 15);
}

TEST(fvec3, VectorPlusOperator)
{
	fvec3 lhs(10, 10, 10);
	fvec3 rhs(15, 20, 10);

	fvec3 r = lhs + rhs;

	EXPECT_EQ(r.x, 25);
	EXPECT_EQ(r.y, 30);
	EXPECT_EQ(r.z, 20);
}

TEST(fvec3, VectorMinusOperator)
{
	fvec3 lhs(10, 10, 10);
	fvec3 rhs(15, 20, 10);

	fvec3 r = lhs - rhs;

	EXPECT_EQ(r.x, -5);
	EXPECT_EQ(r.y, -10);
	EXPECT_EQ(r.z, 0);
}

TEST(fvec3, VectorMultiplyOperator)
{
	fvec3 lhs(10, 10, 10);
	fvec3 rhs(5, 2, 5);

	fvec3 r = lhs * rhs;

	EXPECT_EQ(r.x, 50);
	EXPECT_EQ(r.y, 20);
	EXPECT_EQ(r.z, 50);
}

TEST(fvec3, ScalarMultiplyOperator)
{
	fvec3 lhs(10, 10, 5);
	fvec3 r = lhs * 2.0f;

	EXPECT_EQ(r.x, 20);
	EXPECT_EQ(r.y, 20);
	EXPECT_EQ(r.z, 10);
}

TEST(fvec3, VectorDivideOperator)
{
	fvec3 lhs(10, 10, 20);
	fvec3 rhs(5, 2, 2);

	fvec3 r = lhs / rhs;

	EXPECT_EQ(r.x, 2);
	EXPECT_EQ(r.y, 5);
	EXPECT_EQ(r.z, 10);
}

TEST(fvec3, ScalarDivideOperator)
{
	fvec3 lhs(10, 10, 10);
	fvec3 r = lhs / 2.0f;

	EXPECT_EQ(r.x, 5);
	EXPECT_EQ(r.y, 5);
	EXPECT_EQ(r.z, 5);
}

TEST(fvec3, NegateOperator)
{
	fvec3 v(10, 5, 2);
	v = -v;

	EXPECT_EQ(v.x, -10);
	EXPECT_EQ(v.y, -5);
	EXPECT_EQ(v.z, -2);
}

// DVEC3 TESTS

TEST(dvec3, DefaultConstructor)
{
	dvec3 v;
	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
	EXPECT_EQ(v.z, 0);
}

TEST(dvec3, ComponentConstructor)
{
	dvec3 v(10, 15, 20);
	EXPECT_EQ(v.x, 10);
	EXPECT_EQ(v.y, 15);
	EXPECT_EQ(v.z, 20);
}

TEST(dvec3, ScalarConstructor)
{
	dvec3 v(2);
	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 2);
	EXPECT_EQ(v.z, 2);
}

TEST(dvec3, ArrayConstructor)
{
	f64 values[] = {
		2.0, 10.0, 20.0
	};

	dvec3 v(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 20);
}

TEST(dvec3, CopyConstructor)
{
	dvec3 orig(5, 10, 15);
	dvec3 v(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 15);
}

TEST(dvec3, MoveConstructor)
{
	dvec3 orig(5, 10, 15);
	dvec3 v = std::move(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 15);
}

TEST(dvec3, CopyAssignment)
{
	dvec3 orig(2, 5, 10);
	dvec3 v;
	v = orig;

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 10);
}

TEST(dvec3, MoveAssignment)
{
	dvec3 orig(2, 5, 10);
	dvec3 v;
	v = std::move(orig);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 10);
}

TEST(dvec3, Zero)
{
	dvec3 v(10, 10, 20);
	v.zero();

	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
	EXPECT_EQ(v.z, 0);
}

TEST(dvec3, ComponentSet)
{
	dvec3 v;
	v.set(15, 5, 2);

	EXPECT_EQ(v.x, 15);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 2);
}

TEST(dvec3, ArraySet)
{
	f64 values[] = {
		2.0, 10.0, 20.0
	};

	dvec3 v;
	v.set(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 20);
}

TEST(dvec3, Equals)
{
	dvec3 lhs(10, 15, 20);
	dvec3 rhs(10, 15, 20);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(dvec3, NotEquals)
{
	dvec3 lhs(10, 15, 20);
	dvec3 rhs(10, 10, 5);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(dvec3, VectorPlusEquals)
{
	dvec3 lhs(10, 10, 10);
	dvec3 rhs(5, 2, 5);

	lhs += rhs;

	EXPECT_EQ(lhs.x, 15);
	EXPECT_EQ(lhs.y, 12);
	EXPECT_EQ(lhs.z, 15);
}

TEST(dvec3, VectorMinusEquals)
{
	dvec3 lhs(10, 10, 10);
	dvec3 rhs(5, 2, 5);

	lhs -= rhs;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 8);
	EXPECT_EQ(lhs.z, 5);
}

TEST(dvec3, VectorTimesEquals)
{
	dvec3 lhs(10, 10, 10);
	dvec3 rhs(5, 2, 5);

	lhs *= rhs;

	EXPECT_EQ(lhs.x, 50);
	EXPECT_EQ(lhs.y, 20);
	EXPECT_EQ(lhs.z, 50);
}

TEST(dvec3, ScalarTimesEquals)
{
	dvec3 lhs(10, 10, 10);

	lhs *= 2.0f;

	EXPECT_EQ(lhs.x, 20);
	EXPECT_EQ(lhs.y, 20);
	EXPECT_EQ(lhs.z, 20);
}

TEST(dvec3, VectorDivideEquals)
{
	dvec3 lhs(10, 10, 10);
	dvec3 rhs(5, 2, 5);

	lhs /= rhs;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 5);
	EXPECT_EQ(lhs.z, 2);
}

TEST(dvec3, ScalarDivideEquals)
{
	dvec3 lhs(10, 10, 10);

	lhs /= 2.0f;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 5);
	EXPECT_EQ(lhs.z, 5);
}

TEST(dvec3, Dot)
{
	dvec3 lhs(10, 15, 20);
	dvec3 rhs(5, 5, 5);

	f64 d = lhs.dot(rhs);

	EXPECT_EQ(d, 225);
}

TEST(dvec3, Length)
{
	dvec3 v(15, 20, 25);

	f64 l = v.length();

	EXPECT_EQ(l, sml::sqrt(1250.0));
}

TEST(dvec3, LengthSquared)
{
	dvec3 v(15, 20, 25);

	f64 l = v.lengthsquared();

	EXPECT_EQ(l, 1250);
}

TEST(dvec3, Normalize)
{
	dvec3 v(10, 15, 10);
	f64 l = v.length();
	v.normalize();

	EXPECT_EQ(v.x, 10 / l);
	EXPECT_EQ(v.y, 15 / l);
	EXPECT_EQ(v.z, 10 / l);

	EXPECT_EQ(v.length(), 1);
}

TEST(dvec3, Distance)
{
	dvec3 lhs(0, 0, 0);
	dvec3 rhs(10, 0, 0);

	f64 d = dvec3::distance(lhs, rhs);

	EXPECT_EQ(d, 10);
}

TEST(dvec3, Min)
{
	dvec3 lhs(10, 15, 20);
	dvec3 rhs(4, 25, 40);

	dvec3 m = dvec3::min(lhs, rhs);

	EXPECT_EQ(m.x, 4);
	EXPECT_EQ(m.y, 15);
	EXPECT_EQ(m.z, 20);
}

TEST(dvec3, Max)
{
	dvec3 lhs(10, 15, 20);
	dvec3 rhs(4, 25, 40);

	dvec3 m = dvec3::max(lhs, rhs);

	EXPECT_EQ(m.x, 10);
	EXPECT_EQ(m.y, 25);
	EXPECT_EQ(m.z, 40);
}

TEST(dvec3, Clamp)
{
	dvec3 min(10, 10, 10);
	dvec3 max(20, 20, 20);
	dvec3 val(25, 5, 14);

	dvec3 c = dvec3::clamp(val, min, max);

	EXPECT_EQ(c.x, 20);
	EXPECT_EQ(c.y, 10);
	EXPECT_EQ(c.z, 14);
}

TEST(dvec3, Lerp)
{
	dvec3 lhs(10, 10, 10);
	dvec3 rhs(20, 20, 20);

	dvec3 l = dvec3::lerp(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
	EXPECT_EQ(l.z, 15);
}

TEST(dvec3, LerpClamped)
{
	dvec3 lhs(10, 10, 10);
	dvec3 rhs(20, 20, 20);

	dvec3 l = dvec3::lerpclamped(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
	EXPECT_EQ(l.z, 15);
}

TEST(dvec3, VectorPlusOperator)
{
	dvec3 lhs(10, 10, 10);
	dvec3 rhs(15, 20, 10);

	dvec3 r = lhs + rhs;

	EXPECT_EQ(r.x, 25);
	EXPECT_EQ(r.y, 30);
	EXPECT_EQ(r.z, 20);
}

TEST(dvec3, VectorMinusOperator)
{
	dvec3 lhs(10, 10, 10);
	dvec3 rhs(15, 20, 10);

	dvec3 r = lhs - rhs;

	EXPECT_EQ(r.x, -5);
	EXPECT_EQ(r.y, -10);
	EXPECT_EQ(r.z, 0);
}

TEST(dvec3, VectorMultiplyOperator)
{
	dvec3 lhs(10, 10, 10);
	dvec3 rhs(5, 2, 5);

	dvec3 r = lhs * rhs;

	EXPECT_EQ(r.x, 50);
	EXPECT_EQ(r.y, 20);
	EXPECT_EQ(r.z, 50);
}

TEST(dvec3, ScalarMultiplyOperator)
{
	dvec3 lhs(10, 10, 5);
	dvec3 r = lhs * 2.0;

	EXPECT_EQ(r.x, 20);
	EXPECT_EQ(r.y, 20);
	EXPECT_EQ(r.z, 10);
}

TEST(dvec3, VectorDivideOperator)
{
	dvec3 lhs(10, 10, 20);
	dvec3 rhs(5, 2, 2);

	dvec3 r = lhs / rhs;

	EXPECT_EQ(r.x, 2);
	EXPECT_EQ(r.y, 5);
	EXPECT_EQ(r.z, 10);
}

TEST(dvec3, ScalarDivideOperator)
{
	dvec3 lhs(10, 10, 10);
	dvec3 r = lhs / 2.0;

	EXPECT_EQ(r.x, 5);
	EXPECT_EQ(r.y, 5);
	EXPECT_EQ(r.z, 5);
}

TEST(dvec3, NegateOperator)
{
	dvec3 v(10, 5, 2);
	v = -v;

	EXPECT_EQ(v.x, -10);
	EXPECT_EQ(v.y, -5);
	EXPECT_EQ(v.z, -2);
}

#include "vec4.h"

// FVEC4 TESTS

TEST(fvec4, DefaultConstructor)
{
	fvec4 v;
	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
	EXPECT_EQ(v.z, 0);
	EXPECT_EQ(v.w, 0);
}

TEST(fvec4, ComponentConstructor)
{
	fvec4 v(10, 15, 20, 5);
	EXPECT_EQ(v.x, 10);
	EXPECT_EQ(v.y, 15);
	EXPECT_EQ(v.z, 20);
	EXPECT_EQ(v.w, 5);
}

TEST(fvec4, ScalarConstructor)
{
	fvec4 v(2);
	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 2);
	EXPECT_EQ(v.z, 2);
	EXPECT_EQ(v.w, 2);
}

TEST(fvec4, ArrayConstructor)
{
	f32 values[] = {
		2.0f, 10.0f, 20.0f, 5.0f
	};

	fvec4 v(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 20);
	EXPECT_EQ(v.w, 5);
}

TEST(fvec4, CopyConstructor)
{
	fvec4 orig(5, 10, 15, 10);
	fvec4 v(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 15);
	EXPECT_EQ(v.w, 10);
}

TEST(fvec4, MoveConstructor)
{
	fvec4 orig(5, 10, 15, 10);
	fvec4 v = std::move(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 15);
	EXPECT_EQ(v.w, 10);
}

TEST(fvec4, CopyAssignment)
{
	fvec4 orig(2, 5, 10, 5);
	fvec4 v;
	v = orig;

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 10);
	EXPECT_EQ(v.w, 5);
}

TEST(fvec4, MoveAssignment)
{
	fvec4 orig(2, 5, 10, 2);
	fvec4 v;
	v = std::move(orig);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 10);
	EXPECT_EQ(v.w, 2);
}

TEST(fvec4, Zero)
{
	fvec4 v(10, 10, 20, 5);
	v.zero();

	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
	EXPECT_EQ(v.z, 0);
	EXPECT_EQ(v.w, 0);
}

TEST(fvec4, ComponentSet)
{
	fvec4 v;
	v.set(15, 5, 2, 5);

	EXPECT_EQ(v.x, 15);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 2);
	EXPECT_EQ(v.w, 5);
}

TEST(fvec4, ArraySet)
{
	f32 values[] = {
		2.0f, 10.0f, 20.0f, 5.0f
	};

	fvec4 v;
	v.set(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 20);
	EXPECT_EQ(v.w, 5);
}

TEST(fvec4, Equals)
{
	fvec4 lhs(10, 15, 20, 5);
	fvec4 rhs(10, 15, 20, 5);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(fvec4, NotEquals)
{
	fvec4 lhs(10, 15, 20, 10);
	fvec4 rhs(10, 10, 5, 5);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(fvec4, VectorPlusEquals)
{
	fvec4 lhs(10, 10, 10, 10);
	fvec4 rhs(5, 2, 5, 2);

	lhs += rhs;

	EXPECT_EQ(lhs.x, 15);
	EXPECT_EQ(lhs.y, 12);
	EXPECT_EQ(lhs.z, 15);
	EXPECT_EQ(lhs.w, 12);
}

TEST(fvec4, VectorMinusEquals)
{
	fvec4 lhs(10, 10, 10, 20);
	fvec4 rhs(5, 2, 5, 2);

	lhs -= rhs;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 8);
	EXPECT_EQ(lhs.z, 5);
	EXPECT_EQ(lhs.w, 18);
}

TEST(fvec4, VectorTimesEquals)
{
	fvec4 lhs(10, 10, 10, 20);
	fvec4 rhs(5, 2, 5, 2);

	lhs *= rhs;

	EXPECT_EQ(lhs.x, 50);
	EXPECT_EQ(lhs.y, 20);
	EXPECT_EQ(lhs.z, 50);
	EXPECT_EQ(lhs.w, 40);
}

TEST(fvec4, ScalarTimesEquals)
{
	fvec4 lhs(10, 10, 10, 10);

	lhs *= 2.0f;

	EXPECT_EQ(lhs.x, 20);
	EXPECT_EQ(lhs.y, 20);
	EXPECT_EQ(lhs.z, 20);
	EXPECT_EQ(lhs.w, 20);
}

TEST(fvec4, VectorDivideEquals)
{
	fvec4 lhs(10, 10, 10, 10);
	fvec4 rhs(5, 2, 5, 2);

	lhs /= rhs;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 5);
	EXPECT_EQ(lhs.z, 2);
	EXPECT_EQ(lhs.w, 5);
}

TEST(fvec4, ScalarDivideEquals)
{
	fvec4 lhs(10, 10, 10, 10);

	lhs /= 2.0f;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 5);
	EXPECT_EQ(lhs.z, 5);
	EXPECT_EQ(lhs.w, 5);
}

TEST(fvec4, Dot)
{
	fvec4 lhs(10, 15, 20, 5);
	fvec4 rhs(5, 5, 5, 5);

	f32 d = lhs.dot(rhs);

	EXPECT_EQ(d, 250);
}

TEST(fvec4, Length)
{
	fvec4 v(15, 20, 25, 30);

	f32 l = v.length();

	EXPECT_EQ(l, sml::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w)));
}

TEST(fvec4, LengthSquared)
{
	fvec4 v(15, 20, 25, 5);

	f32 l = v.lengthsquared();

	EXPECT_EQ(l, (v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

TEST(fvec4, Normalize)
{
	fvec4 v(10, 15, 10, 5);
	f32 l = v.length();
	v.normalize();

	EXPECT_EQ(v.x, 10 / l);
	EXPECT_EQ(v.y, 15 / l);
	EXPECT_EQ(v.z, 10 / l);
	EXPECT_EQ(v.w, 5 / l);

	EXPECT_EQ(v.length(), 1);
}

TEST(fvec4, Distance)
{
	fvec4 lhs(0, 0, 0, 0);
	fvec4 rhs(10, 0, 0, 0);

	f32 d = fvec4::distance(lhs, rhs);

	EXPECT_EQ(d, 10);
}

TEST(fvec4, Min)
{
	fvec4 lhs(10, 15, 20, 30);
	fvec4 rhs(4, 25, 40, 5);

	fvec4 m = fvec4::min(lhs, rhs);

	EXPECT_EQ(m.x, 4);
	EXPECT_EQ(m.y, 15);
	EXPECT_EQ(m.z, 20);
	EXPECT_EQ(m.w, 5);
}

TEST(fvec4, Max)
{
	fvec4 lhs(10, 15, 20, 50);
	fvec4 rhs(4, 25, 40, 4);

	fvec4 m = fvec4::max(lhs, rhs);

	EXPECT_EQ(m.x, 10);
	EXPECT_EQ(m.y, 25);
	EXPECT_EQ(m.z, 40);
	EXPECT_EQ(m.w, 50);
}

TEST(fvec4, Clamp)
{
	fvec4 min(10, 10, 10, 10);
	fvec4 max(20, 20, 20, 20);
	fvec4 val(25, 5, 14, 25);

	fvec4 c = fvec4::clamp(val, min, max);

	EXPECT_EQ(c.x, 20);
	EXPECT_EQ(c.y, 10);
	EXPECT_EQ(c.z, 14);
	EXPECT_EQ(c.w, 20);
}

TEST(fvec4, Lerp)
{
	fvec4 lhs(10, 10, 10, 10);
	fvec4 rhs(20, 20, 20, 20);

	fvec4 l = fvec4::lerp(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
	EXPECT_EQ(l.z, 15);
	EXPECT_EQ(l.w, 15);
}

TEST(fvec4, LerpClamped)
{
	fvec4 lhs(10, 10, 10, 10);
	fvec4 rhs(20, 20, 20, 20);

	fvec4 l = fvec4::lerpclamped(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
	EXPECT_EQ(l.z, 15);
	EXPECT_EQ(l.w, 15);
}

TEST(fvec4, VectorPlusOperator)
{
	fvec4 lhs(10, 10, 10, 10);
	fvec4 rhs(15, 20, 10, 20);

	fvec4 r = lhs + rhs;

	EXPECT_EQ(r.x, 25);
	EXPECT_EQ(r.y, 30);
	EXPECT_EQ(r.z, 20);
	EXPECT_EQ(r.w, 30);
}

TEST(fvec4, VectorMinusOperator)
{
	fvec4 lhs(10, 10, 10, 10);
	fvec4 rhs(15, 20, 10, 20);

	fvec4 r = lhs - rhs;

	EXPECT_EQ(r.x, -5);
	EXPECT_EQ(r.y, -10);
	EXPECT_EQ(r.z, 0);
	EXPECT_EQ(r.w, -10);
}

TEST(fvec4, VectorMultiplyOperator)
{
	fvec4 lhs(10, 10, 10, 10);
	fvec4 rhs(5, 2, 5, 2);

	fvec4 r = lhs * rhs;

	EXPECT_EQ(r.x, 50);
	EXPECT_EQ(r.y, 20);
	EXPECT_EQ(r.z, 50);
	EXPECT_EQ(r.w, 20);
}

TEST(fvec4, ScalarMultiplyOperator)
{
	fvec4 lhs(10, 10, 5, 5);
	fvec4 r = lhs * 2.0f;

	EXPECT_EQ(r.x, 20);
	EXPECT_EQ(r.y, 20);
	EXPECT_EQ(r.z, 10);
	EXPECT_EQ(r.w, 10);
}

TEST(fvec4, VectorDivideOperator)
{
	fvec4 lhs(10, 10, 20, 20);
	fvec4 rhs(5, 2, 2, 2);

	fvec4 r = lhs / rhs;

	EXPECT_EQ(r.x, 2);
	EXPECT_EQ(r.y, 5);
	EXPECT_EQ(r.z, 10);
	EXPECT_EQ(r.w, 10);
}

TEST(fvec4, ScalarDivideOperator)
{
	fvec4 lhs(10, 10, 10, 10);
	fvec4 r = lhs / 2.0f;

	EXPECT_EQ(r.x, 5);
	EXPECT_EQ(r.y, 5);
	EXPECT_EQ(r.z, 5);
	EXPECT_EQ(r.w, 5);
}

TEST(fvec4, NegateOperator)
{
	fvec4 v(10, 5, 2, 1);
	v = -v;

	EXPECT_EQ(v.x, -10);
	EXPECT_EQ(v.y, -5);
	EXPECT_EQ(v.z, -2);
	EXPECT_EQ(v.w, -1);
}

// DVEC4 TESTS

TEST(dvec4, DefaultConstructor)
{
	dvec4 v;
	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
	EXPECT_EQ(v.z, 0);
	EXPECT_EQ(v.w, 0);
}

TEST(dvec4, ComponentConstructor)
{
	dvec4 v(10, 15, 20, 5);
	EXPECT_EQ(v.x, 10);
	EXPECT_EQ(v.y, 15);
	EXPECT_EQ(v.z, 20);
	EXPECT_EQ(v.w, 5);
}

TEST(dvec4, ScalarConstructor)
{
	dvec4 v(2);
	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 2);
	EXPECT_EQ(v.z, 2);
	EXPECT_EQ(v.w, 2);
}

TEST(dvec4, ArrayConstructor)
{
	f64 values[] = {
		2.0, 10.0, 20.0, 5.0
	};

	dvec4 v(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 20);
	EXPECT_EQ(v.w, 5);
}

TEST(dvec4, CopyConstructor)
{
	dvec4 orig(5, 10, 15, 10);
	dvec4 v(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 15);
	EXPECT_EQ(v.w, 10);
}

TEST(dvec4, MoveConstructor)
{
	dvec4 orig(5, 10, 15, 10);
	dvec4 v = std::move(orig);

	EXPECT_EQ(v.x, 5);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 15);
	EXPECT_EQ(v.w, 10);
}

TEST(dvec4, CopyAssignment)
{
	dvec4 orig(2, 5, 10, 5);
	dvec4 v;
	v = orig;

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 10);
	EXPECT_EQ(v.w, 5);
}

TEST(dvec4, MoveAssignment)
{
	dvec4 orig(2, 5, 10, 2);
	dvec4 v;
	v = std::move(orig);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 10);
	EXPECT_EQ(v.w, 2);
}

TEST(dvec4, Zero)
{
	dvec4 v(10, 10, 20, 5);
	v.zero();

	EXPECT_EQ(v.x, 0);
	EXPECT_EQ(v.y, 0);
	EXPECT_EQ(v.z, 0);
	EXPECT_EQ(v.w, 0);
}

TEST(dvec4, ComponentSet)
{
	dvec4 v;
	v.set(15, 5, 2, 5);

	EXPECT_EQ(v.x, 15);
	EXPECT_EQ(v.y, 5);
	EXPECT_EQ(v.z, 2);
	EXPECT_EQ(v.w, 5);
}

TEST(dvec4, ArraySet)
{
	f64 values[] = {
		2.0, 10.0, 20.0, 5.0
	};

	dvec4 v;
	v.set(values);

	EXPECT_EQ(v.x, 2);
	EXPECT_EQ(v.y, 10);
	EXPECT_EQ(v.z, 20);
	EXPECT_EQ(v.w, 5);
}

TEST(dvec4, Equals)
{
	dvec4 lhs(10, 15, 20, 5);
	dvec4 rhs(10, 15, 20, 5);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(dvec4, NotEquals)
{
	dvec4 lhs(10, 15, 20, 10);
	dvec4 rhs(10, 10, 5, 5);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(dvec4, VectorPlusEquals)
{
	dvec4 lhs(10, 10, 10, 10);
	dvec4 rhs(5, 2, 5, 2);

	lhs += rhs;

	EXPECT_EQ(lhs.x, 15);
	EXPECT_EQ(lhs.y, 12);
	EXPECT_EQ(lhs.z, 15);
	EXPECT_EQ(lhs.w, 12);
}

TEST(dvec4, VectorMinusEquals)
{
	dvec4 lhs(10, 10, 10, 20);
	dvec4 rhs(5, 2, 5, 2);

	lhs -= rhs;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 8);
	EXPECT_EQ(lhs.z, 5);
	EXPECT_EQ(lhs.w, 18);
}

TEST(dvec4, VectorTimesEquals)
{
	dvec4 lhs(10, 10, 10, 20);
	dvec4 rhs(5, 2, 5, 2);

	lhs *= rhs;

	EXPECT_EQ(lhs.x, 50);
	EXPECT_EQ(lhs.y, 20);
	EXPECT_EQ(lhs.z, 50);
	EXPECT_EQ(lhs.w, 40);
}

TEST(dvec4, ScalarTimesEquals)
{
	dvec4 lhs(10, 10, 10, 10);

	lhs *= 2.0;

	EXPECT_EQ(lhs.x, 20);
	EXPECT_EQ(lhs.y, 20);
	EXPECT_EQ(lhs.z, 20);
	EXPECT_EQ(lhs.w, 20);
}

TEST(dvec4, VectorDivideEquals)
{
	dvec4 lhs(10, 10, 10, 10);
	dvec4 rhs(5, 2, 5, 2);

	lhs /= rhs;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 5);
	EXPECT_EQ(lhs.z, 2);
	EXPECT_EQ(lhs.w, 5);
}

TEST(dvec4, ScalarDivideEquals)
{
	dvec4 lhs(10, 10, 10, 10);

	lhs /= 2.0;

	EXPECT_EQ(lhs.x, 5);
	EXPECT_EQ(lhs.y, 5);
	EXPECT_EQ(lhs.z, 5);
	EXPECT_EQ(lhs.w, 5);
}

TEST(dvec4, Dot)
{
	dvec4 lhs(10, 15, 20, 5);
	dvec4 rhs(5, 5, 5, 5);

	f64 d = lhs.dot(rhs);

	EXPECT_EQ(d, 250);
}

TEST(dvec4, Length)
{
	dvec4 v(15, 20, 25, 30);

	f64 l = v.length();

	EXPECT_EQ(l, sml::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w)));
}

TEST(dvec4, LengthSquared)
{
	dvec4 v(15, 20, 25, 5);

	f64 l = v.lengthsquared();

	EXPECT_EQ(l, (v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

TEST(dvec4, Normalize)
{
	dvec4 v(10, 15, 10, 5);
	f64 l = v.length();
	v.normalize();

	EXPECT_EQ(v.x, 10 / l);
	EXPECT_EQ(v.y, 15 / l);
	EXPECT_EQ(v.z, 10 / l);
	EXPECT_EQ(v.w, 5 / l);

	EXPECT_FLOAT_EQ(v.length(), 1);
}

TEST(dvec4, Distance)
{
	dvec4 lhs(0, 0, 0, 0);
	dvec4 rhs(10, 0, 0, 0);

	f64 d = dvec4::distance(lhs, rhs);

	EXPECT_EQ(d, 10);
}

TEST(dvec4, Min)
{
	dvec4 lhs(10, 15, 20, 30);
	dvec4 rhs(4, 25, 40, 5);

	dvec4 m = dvec4::min(lhs, rhs);

	EXPECT_EQ(m.x, 4);
	EXPECT_EQ(m.y, 15);
	EXPECT_EQ(m.z, 20);
	EXPECT_EQ(m.w, 5);
}

TEST(dvec4, Max)
{
	dvec4 lhs(10, 15, 20, 50);
	dvec4 rhs(4, 25, 40, 4);

	dvec4 m = dvec4::max(lhs, rhs);

	EXPECT_EQ(m.x, 10);
	EXPECT_EQ(m.y, 25);
	EXPECT_EQ(m.z, 40);
	EXPECT_EQ(m.w, 50);
}

TEST(dvec4, Clamp)
{
	dvec4 min(10, 10, 10, 10);
	dvec4 max(20, 20, 20, 20);
	dvec4 val(25, 5, 14, 25);

	dvec4 c = dvec4::clamp(val, min, max);

	EXPECT_EQ(c.x, 20);
	EXPECT_EQ(c.y, 10);
	EXPECT_EQ(c.z, 14);
	EXPECT_EQ(c.w, 20);
}

TEST(dvec4, Lerp)
{
	dvec4 lhs(10, 10, 10, 10);
	dvec4 rhs(20, 20, 20, 20);

	dvec4 l = dvec4::lerp(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
	EXPECT_EQ(l.z, 15);
	EXPECT_EQ(l.w, 15);
}

TEST(dvec4, LerpClamped)
{
	dvec4 lhs(10, 10, 10, 10);
	dvec4 rhs(20, 20, 20, 20);

	dvec4 l = dvec4::lerpclamped(lhs, rhs, 0.5);

	EXPECT_EQ(l.x, 15);
	EXPECT_EQ(l.y, 15);
	EXPECT_EQ(l.z, 15);
	EXPECT_EQ(l.w, 15);
}

TEST(dvec4, VectorPlusOperator)
{
	dvec4 lhs(10, 10, 10, 10);
	dvec4 rhs(15, 20, 10, 20);

	dvec4 r = lhs + rhs;

	EXPECT_EQ(r.x, 25);
	EXPECT_EQ(r.y, 30);
	EXPECT_EQ(r.z, 20);
	EXPECT_EQ(r.w, 30);
}

TEST(dvec4, VectorMinusOperator)
{
	dvec4 lhs(10, 10, 10, 10);
	dvec4 rhs(15, 20, 10, 20);

	dvec4 r = lhs - rhs;

	EXPECT_EQ(r.x, -5);
	EXPECT_EQ(r.y, -10);
	EXPECT_EQ(r.z, 0);
	EXPECT_EQ(r.w, -10);
}

TEST(dvec4, VectorMultiplyOperator)
{
	dvec4 lhs(10, 10, 10, 10);
	dvec4 rhs(5, 2, 5, 2);

	dvec4 r = lhs * rhs;

	EXPECT_EQ(r.x, 50);
	EXPECT_EQ(r.y, 20);
	EXPECT_EQ(r.z, 50);
	EXPECT_EQ(r.w, 20);
}

TEST(dvec4, ScalarMultiplyOperator)
{
	dvec4 lhs(10, 10, 5, 5);
	dvec4 r = lhs * 2.0;

	EXPECT_EQ(r.x, 20);
	EXPECT_EQ(r.y, 20);
	EXPECT_EQ(r.z, 10);
	EXPECT_EQ(r.w, 10);
}

TEST(dvec4, VectorDivideOperator)
{
	dvec4 lhs(10, 10, 20, 20);
	dvec4 rhs(5, 2, 2, 2);

	dvec4 r = lhs / rhs;

	EXPECT_EQ(r.x, 2);
	EXPECT_EQ(r.y, 5);
	EXPECT_EQ(r.z, 10);
	EXPECT_EQ(r.w, 10);
}

TEST(dvec4, ScalarDivideOperator)
{
	dvec4 lhs(10, 10, 10, 10);
	dvec4 r = lhs / 2.0;

	EXPECT_EQ(r.x, 5);
	EXPECT_EQ(r.y, 5);
	EXPECT_EQ(r.z, 5);
	EXPECT_EQ(r.w, 5);
}

TEST(dvec4, NegateOperator)
{
	dvec4 v(10, 5, 2, 1);
	v = -v;

	EXPECT_EQ(v.x, -10);
	EXPECT_EQ(v.y, -5);
	EXPECT_EQ(v.z, -2);
	EXPECT_EQ(v.w, -1);
}