#include <quat.h>

#include <gtest/gtest.h>

using namespace sml;

// FQUAT Tests

TEST(fquat, DefaultConstructor)
{
	fquat q;

	EXPECT_EQ(q.x, 0);
	EXPECT_EQ(q.y, 0);
	EXPECT_EQ(q.z, 0);
	EXPECT_EQ(q.w, 0);
}

TEST(fquat, ComponentConstructor)
{
	fquat q(1, 2, 3, 4);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, VectorScalarConstructor)
{
	fquat q({ 1, 2, 3 }, 4);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, ScalarVectorConstructor)
{
	fquat q(4, { 1, 2, 3 });

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, ArrayConstructor)
{
	f32 values[] = {
		1, 2, 3, 4
	};

	fquat q(values);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, VectorConstructor)
{
	fvec4 v(1, 2, 3, 4);
	fquat q(v);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, ScalarConstructor)
{
	fquat q(2);

	EXPECT_EQ(q.x, 2);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 2);
	EXPECT_EQ(q.w, 2);
}

TEST(fquat, CopyConstructor)
{
	fquat lhs(1, 2, 3, 4);
	fquat rhs(lhs);

	EXPECT_EQ(rhs.x, 1);
	EXPECT_EQ(rhs.y, 2);
	EXPECT_EQ(rhs.z, 3);
	EXPECT_EQ(rhs.w, 4);
}

TEST(fquat, MoveConstructor)
{
	fquat lhs(1, 2, 3, 4);
	fquat rhs(std::move(lhs));

	EXPECT_EQ(rhs.x, 1);
	EXPECT_EQ(rhs.y, 2);
	EXPECT_EQ(rhs.z, 3);
	EXPECT_EQ(rhs.w, 4);
}

TEST(fquat, Zero)
{
	fquat q(1, 2, 3, 4);
	q.zero();

	EXPECT_EQ(q.x, 0);
	EXPECT_EQ(q.y, 0);
	EXPECT_EQ(q.z, 0);
	EXPECT_EQ(q.w, 0);
}

TEST(fquat, ComponentSet)
{
	fquat q(1, 1, 1, 1);
	q.set(1, 2, 3, 4);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, ArraySet)
{
	f32 values[] = {
		1, 2, 3, 4
	};

	fquat q;
	q.set(values);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, VectorSet)
{
	fvec4 v(1, 2, 3, 4);
	fquat q;

	q.set(v);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, VectorScalarSet)
{
	fvec3 v(1, 2, 3);
	fquat q;
	
	q.set(v, 4);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, ScalarVectorSet)
{
	fvec3 v(1, 2, 3);
	fquat q;

	q.set(4, v);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, Equals)
{
	fquat lhs(1, 2, 3, 4);
	fquat rhs(1, 2, 3, 4);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(fquat, NotEquals)
{
	fquat lhs(1, 2, 3, 4);
	fquat rhs(1, 3, 3, 4);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(fquat, CopyAssign)
{
	fquat lhs(1, 2, 3, 4);
	fquat rhs;

	rhs = lhs;

	EXPECT_EQ(rhs.x, 1);
	EXPECT_EQ(rhs.y, 2);
	EXPECT_EQ(rhs.z, 3);
	EXPECT_EQ(rhs.w, 4);
}

TEST(fquat, MoveAssign)
{
	fquat lhs(1, 2, 3, 4);
	fquat rhs;

	rhs = std::move(lhs);

	EXPECT_EQ(rhs.x, 1);
	EXPECT_EQ(rhs.y, 2);
	EXPECT_EQ(rhs.z, 3);
	EXPECT_EQ(rhs.w, 4);
}

TEST(fquat, PlusEqualsOperator)
{
	fquat lhs(1, 2, 3, 4);
	fquat rhs(1, 2, 3, 4);

	lhs += rhs;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 4);
	EXPECT_EQ(lhs.z, 6);
	EXPECT_EQ(lhs.w, 8);
}

TEST(fquat, MinusEqualsOperator)
{
	fquat lhs(1, 2, 3, 4);
	fquat rhs(1, 2, 3, 4);

	lhs -= rhs;

	EXPECT_EQ(lhs.x, 0);
	EXPECT_EQ(lhs.y, 0);
	EXPECT_EQ(lhs.z, 0);
	EXPECT_EQ(lhs.w, 0);
}

TEST(fquat, TimesEqualsOperator)
{
	fquat lhs(0.5, 0.5, 0.5, 0.5);
	fquat rhs(0.5, 0.5, 0.5, 0.5);

	lhs *= rhs;

	EXPECT_EQ(lhs.x, 0.5);
	EXPECT_EQ(lhs.y, 0.5);
	EXPECT_EQ(lhs.z, 0.5);
	EXPECT_EQ(lhs.w, -0.5);
}

TEST(fquat, TimesEqualsScalarOperator)
{
	fquat lhs(1, 2, 3, 4);

	lhs *= 2;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 4);
	EXPECT_EQ(lhs.z, 6);
	EXPECT_EQ(lhs.w, 8);
}

TEST(fquat, Normalize)
{
	fquat q(1, 2, 3, 4);
	f32 l = q.length();
	q.normalize();

	EXPECT_EQ(q.x, 1.0f / l);
	EXPECT_EQ(q.y, 2.0f / l);
	EXPECT_EQ(q.z, 3.0f / l);
	EXPECT_EQ(q.w, 4.0f / l);

	EXPECT_FLOAT_EQ(q.length(), 1);
}

TEST(fquat, Length)
{
	fquat q(1, 2, 3, 4);

	EXPECT_EQ(q.length(), sml::sqrt(30.0f));
}

TEST(fquat, LengthSquared)
{
	fquat q(1, 2, 3, 4);

	EXPECT_EQ(q.lengthsquared(), 30);
}

TEST(fquat, Conjugate)
{
	fquat q(1, 2, 3, 4);

	q = q.conjugate();

	EXPECT_EQ(q.x, -1);
	EXPECT_EQ(q.y, -2);
	EXPECT_EQ(q.z, -3);
	EXPECT_EQ(q.w, 4);
}

TEST(fquat, EulerAngles)
{
	fquat q = fquat::euler(90, 90, 0);

	fvec3 euler = q.eulerAngles();

	EXPECT_EQ(euler.x, 90);
	EXPECT_EQ(euler.y, 90);
	EXPECT_EQ(euler.z, 0);
}

TEST(fquat, Identity)
{
	fquat q(1, 2, 3, 4);
	q = fquat::identity();

	EXPECT_EQ(q.x, 0);
	EXPECT_EQ(q.y, 0);
	EXPECT_EQ(q.z, 0);
	EXPECT_EQ(q.w, 1);
}

// DQUAT Tests

TEST(dquat, DefaultConstructor)
{
	dquat q;

	EXPECT_EQ(q.x, 0);
	EXPECT_EQ(q.y, 0);
	EXPECT_EQ(q.z, 0);
	EXPECT_EQ(q.w, 0);
}

TEST(dquat, ComponentConstructor)
{
	dquat q(1, 2, 3, 4);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, VectorScalarConstructor)
{
	dquat q({ 1, 2, 3 }, 4);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, ScalarVectorConstructor)
{
	dquat q(4, { 1, 2, 3 });

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, ArrayConstructor)
{
	f64 values[] = {
		1, 2, 3, 4
	};

	dquat q(values);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, VectorConstructor)
{
	dvec4 v(1, 2, 3, 4);
	dquat q(v);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, ScalarConstructor)
{
	dquat q(2);

	EXPECT_EQ(q.x, 2);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 2);
	EXPECT_EQ(q.w, 2);
}

TEST(dquat, CopyConstructor)
{
	dquat lhs(1, 2, 3, 4);
	dquat rhs(lhs);

	EXPECT_EQ(rhs.x, 1);
	EXPECT_EQ(rhs.y, 2);
	EXPECT_EQ(rhs.z, 3);
	EXPECT_EQ(rhs.w, 4);
}

TEST(dquat, MoveConstructor)
{
	dquat lhs(1, 2, 3, 4);
	dquat rhs(std::move(lhs));

	EXPECT_EQ(rhs.x, 1);
	EXPECT_EQ(rhs.y, 2);
	EXPECT_EQ(rhs.z, 3);
	EXPECT_EQ(rhs.w, 4);
}

TEST(dquat, Zero)
{
	dquat q(1, 2, 3, 4);
	q.zero();

	EXPECT_EQ(q.x, 0);
	EXPECT_EQ(q.y, 0);
	EXPECT_EQ(q.z, 0);
	EXPECT_EQ(q.w, 0);
}

TEST(dquat, ComponentSet)
{
	dquat q(1, 1, 1, 1);
	q.set(1, 2, 3, 4);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, ArraySet)
{
	f64 values[] = {
		1, 2, 3, 4
	};

	dquat q;
	q.set(values);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, VectorSet)
{
	dvec4 v(1, 2, 3, 4);
	dquat q;

	q.set(v);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, VectorScalarSet)
{
	dvec3 v(1, 2, 3);
	dquat q;

	q.set(v, 4);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, ScalarVectorSet)
{
	dvec3 v(1, 2, 3);
	dquat q;

	q.set(4, v);

	EXPECT_EQ(q.x, 1);
	EXPECT_EQ(q.y, 2);
	EXPECT_EQ(q.z, 3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, Equals)
{
	dquat lhs(1, 2, 3, 4);
	dquat rhs(1, 2, 3, 4);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(dquat, NotEquals)
{
	dquat lhs(1, 2, 3, 4);
	dquat rhs(1, 3, 3, 4);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(dquat, CopyAssign)
{
	dquat lhs(1, 2, 3, 4);
	dquat rhs;

	rhs = lhs;

	EXPECT_EQ(rhs.x, 1);
	EXPECT_EQ(rhs.y, 2);
	EXPECT_EQ(rhs.z, 3);
	EXPECT_EQ(rhs.w, 4);
}

TEST(dquat, MoveAssign)
{
	dquat lhs(1, 2, 3, 4);
	dquat rhs;

	rhs = std::move(lhs);

	EXPECT_EQ(rhs.x, 1);
	EXPECT_EQ(rhs.y, 2);
	EXPECT_EQ(rhs.z, 3);
	EXPECT_EQ(rhs.w, 4);
}

TEST(dquat, PlusEqualsOperator)
{
	dquat lhs(1, 2, 3, 4);
	dquat rhs(1, 2, 3, 4);

	lhs += rhs;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 4);
	EXPECT_EQ(lhs.z, 6);
	EXPECT_EQ(lhs.w, 8);
}

TEST(dquat, MinusEqualsOperator)
{
	dquat lhs(1, 2, 3, 4);
	dquat rhs(1, 2, 3, 4);

	lhs -= rhs;

	EXPECT_EQ(lhs.x, 0);
	EXPECT_EQ(lhs.y, 0);
	EXPECT_EQ(lhs.z, 0);
	EXPECT_EQ(lhs.w, 0);
}

TEST(dquat, TimesEqualsOperator)
{
	dquat lhs(0.5, 0.5, 0.5, 0.5);
	dquat rhs(0.5, 0.5, 0.5, 0.5);

	lhs *= rhs;

	EXPECT_EQ(lhs.x, 0.5);
	EXPECT_EQ(lhs.y, 0.5);
	EXPECT_EQ(lhs.z, 0.5);
	EXPECT_EQ(lhs.w, -0.5);
}

TEST(dquat, TimesEqualsScalarOperator)
{
	dquat lhs(1, 2, 3, 4);

	lhs *= 2;

	EXPECT_EQ(lhs.x, 2);
	EXPECT_EQ(lhs.y, 4);
	EXPECT_EQ(lhs.z, 6);
	EXPECT_EQ(lhs.w, 8);
}

TEST(dquat, Normalize)
{
	dquat q(1, 2, 3, 4);
	f64 l = q.length();
	q.normalize();

	EXPECT_EQ(q.x, 1.0 / l);
	EXPECT_EQ(q.y, 2.0 / l);
	EXPECT_EQ(q.z, 3.0 / l);
	EXPECT_EQ(q.w, 4.0 / l);

	EXPECT_FLOAT_EQ(q.length(), 1);
}

TEST(dquat, Length)
{
	dquat q(1, 2, 3, 4);

	EXPECT_EQ(q.length(), sml::sqrt(30.0));
}

TEST(dquat, LengthSquared)
{
	dquat q(1, 2, 3, 4);

	EXPECT_EQ(q.lengthsquared(), 30);
}

TEST(dquat, Conjugate)
{
	dquat q(1, 2, 3, 4);

	q = q.conjugate();

	EXPECT_EQ(q.x, -1);
	EXPECT_EQ(q.y, -2);
	EXPECT_EQ(q.z, -3);
	EXPECT_EQ(q.w, 4);
}

TEST(dquat, EulerAngles)
{
	dquat q = dquat::euler(90, 90, 0);

	dvec3 euler = q.eulerAngles();

	EXPECT_FLOAT_EQ(euler.x, 90);
	EXPECT_FLOAT_EQ(euler.y, 90);
	EXPECT_FLOAT_EQ(euler.z, 360);
}

TEST(dquat, Identity)
{
	dquat q(1, 2, 3, 4);
	q = dquat::identity();

	EXPECT_EQ(q.x, 0);
	EXPECT_EQ(q.y, 0);
	EXPECT_EQ(q.z, 0);
	EXPECT_EQ(q.w, 1);
}

