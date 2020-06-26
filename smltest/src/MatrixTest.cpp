#include <mat2.h>

#include <gtest/gtest.h>

using namespace sml;

// FMAT Tests

TEST(fmat2, DefaultConstructor)
{
	fmat2 m;

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
}

TEST(fmat2, ComponentConstructor)
{
	fmat2 m(1, 2, 3, 4);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(fmat2, DiagonalConstructor)
{
	fmat2 m(2);

	EXPECT_EQ(m.m00, 2);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 2);
}

TEST(fmat2, ArrayConstructor)
{
	f32 values[] = {
		1, 2, 3, 4
	};

	fmat2 m(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(fmat2, ColumnConstructor)
{
	f32 col1[2] = {
		1, 2
	};

	f32 col2[2] = {
		3, 4
	};

	fmat2 m(col1, col2);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(fmat2, CopyConstructor)
{
	fmat2 lhs(2);
	fmat2 rhs(lhs);

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
}

TEST(fmat2, MoveConstructor)
{
	fmat2 lhs(2);
	fmat2 rhs(std::move(lhs));

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
}

TEST(fmat2, ComponentSet)
{
	fmat2 m;
	m.set(1, 2, 3, 4);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(fmat2, ArraySet)
{
	f32 values[] = {
		1, 2, 3, 4
	};

	fmat2 m;
	m.set(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(fmat2, Equals)
{
	fmat2 lhs(1, 2, 3, 4);
	fmat2 rhs(1, 2, 3, 4);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(fmat2, NotEquals)
{
	fmat2 lhs(1, 3, 3, 4);
	fmat2 rhs(1, 2, 3, 4);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(fmat2, CopyAssign)
{
	fmat2 lhs;
	fmat2 rhs(1, 2, 3, 4);

	lhs = rhs;

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m10, 3);
	EXPECT_EQ(lhs.m11, 4);
}

TEST(fmat2, MoveAssign)
{
	fmat2 lhs;
	fmat2 rhs(1, 2, 3, 4);

	lhs = std::move(rhs);

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m10, 3);
	EXPECT_EQ(lhs.m11, 4);
}

TEST(fmat2, MatrixMultiplyOperator)
{
	fmat2 lhs(1, 2, 3, 4);
	fmat2 rhs(4, 3, 2, 1);

	lhs *= rhs;

	EXPECT_EQ(lhs.m00, 13);
	EXPECT_EQ(lhs.m01, 20);
	EXPECT_EQ(lhs.m10, 5);
	EXPECT_EQ(lhs.m11, 8);
}

TEST(fmat2, Identity)
{
	fmat2 m(2);
	m.identity();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
}

TEST(fmat2, Transpose)
{
	fmat2 m(1, 2, 3, 4);
	m.transpose();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 3);
	EXPECT_EQ(m.m10, 2);
	EXPECT_EQ(m.m11, 4);
}

TEST(fmat2, Invert)
{
	fmat2 m(1, 2, 3, 4);
	m.invert();

	EXPECT_EQ(m.m00, -2);
	EXPECT_EQ(m.m01, 1);
	EXPECT_EQ(m.m10, 3.0f/2.0f);
	EXPECT_EQ(m.m11, -1.0f/2.0f);
}

TEST(fmat2, Negate)
{
	fmat2 m(1, 2, 3, 4);
	m.negate();

	EXPECT_EQ(m.m00, -1);
	EXPECT_EQ(m.m01, -2);
	EXPECT_EQ(m.m10, -3);
	EXPECT_EQ(m.m11, -4);
}

TEST(fmat2, Determinant)
{
	fmat2 m(1, 2, 3, 4);
	f32 d = m.determinant();

	EXPECT_EQ(d, -2);
}

// DMAT2 Tests

TEST(dmat2, DefaultConstructor)
{
	dmat2 m;

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
}

TEST(dmat2, ComponentConstructor)
{
	dmat2 m(1, 2, 3, 4);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(dmat2, DiagonalConstructor)
{
	dmat2 m(2);

	EXPECT_EQ(m.m00, 2);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 2);
}

TEST(dmat2, ArrayConstructor)
{
	f64 values[] = {
		1, 2, 3, 4
	};

	dmat2 m(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(dmat2, ColumnConstructor)
{
	f64 col1[2] = {
		1, 2
	};

	f64 col2[2] = {
		3, 4
	};

	dmat2 m(col1, col2);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(dmat2, CopyConstructor)
{
	dmat2 lhs(2);
	dmat2 rhs(lhs);

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
}

TEST(dmat2, MoveConstructor)
{
	dmat2 lhs(2);
	dmat2 rhs(std::move(lhs));

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
}

TEST(dmat2, ComponentSet)
{
	dmat2 m;
	m.set(1, 2, 3, 4);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(dmat2, ArraySet)
{
	f64 values[] = {
		1, 2, 3, 4
	};

	dmat2 m;
	m.set(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m10, 3);
	EXPECT_EQ(m.m11, 4);
}

TEST(dmat2, Equals)
{
	dmat2 lhs(1, 2, 3, 4);
	dmat2 rhs(1, 2, 3, 4);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(dmat2, NotEquals)
{
	dmat2 lhs(1, 3, 3, 4);
	dmat2 rhs(1, 2, 3, 4);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(dmat2, CopyAssign)
{
	dmat2 lhs;
	dmat2 rhs(1, 2, 3, 4);

	lhs = rhs;

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m10, 3);
	EXPECT_EQ(lhs.m11, 4);
}

TEST(dmat2, MoveAssign)
{
	dmat2 lhs;
	dmat2 rhs(1, 2, 3, 4);

	lhs = std::move(rhs);

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m10, 3);
	EXPECT_EQ(lhs.m11, 4);
}

TEST(dmat2, MatrixMultiplyOperator)
{
	dmat2 lhs(1, 2, 3, 4);
	dmat2 rhs(4, 3, 2, 1);

	lhs *= rhs;

	EXPECT_EQ(lhs.m00, 13);
	EXPECT_EQ(lhs.m01, 20);
	EXPECT_EQ(lhs.m10, 5);
	EXPECT_EQ(lhs.m11, 8);
}

TEST(dmat2, Identity)
{
	dmat2 m(2);
	m.identity();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
}

TEST(dmat2, Transpose)
{
	dmat2 m(1, 2, 3, 4);
	m.transpose();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 3);
	EXPECT_EQ(m.m10, 2);
	EXPECT_EQ(m.m11, 4);
}

TEST(dmat2, Invert)
{
	dmat2 m(1, 2, 3, 4);
	m.invert();

	EXPECT_EQ(m.m00, -2);
	EXPECT_EQ(m.m01, 1);
	EXPECT_EQ(m.m10, 3.0 / 2.0);
	EXPECT_EQ(m.m11, -1.0 / 2.0);
}

TEST(dmat2, Negate)
{
	dmat2 m(1, 2, 3, 4);
	m.negate();

	EXPECT_EQ(m.m00, -1);
	EXPECT_EQ(m.m01, -2);
	EXPECT_EQ(m.m10, -3);
	EXPECT_EQ(m.m11, -4);
}

TEST(dmat2, Determinant)
{
	dmat2 m(1, 2, 3, 4);
	f64 d = m.determinant();

	EXPECT_EQ(d, -2);
}

#include <mat3.h>

// FMAT3 Tests

TEST(fmat3, DefaultConstructor)
{
	fmat3 m;

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 1);
}

TEST(fmat3, ComponentConstructor)
{
	fmat3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(fmat3, DiagonalConstructor)
{
	fmat3 m(2);

	EXPECT_EQ(m.m00, 2);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 2);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 2);
}

TEST(fmat3, ArrayConstructor)
{
	f32 values[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	fmat3 m(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(fmat3, ColumnConstructor)
{
	f32 col1[3] = {
		1, 2, 3
	};

	f32 col2[3] = {
		4, 5, 6
	};

	f32 col3[3] = {
		7, 8, 9
	};

	fmat3 m(col1, col2, col3);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(fmat3, CopyConstructor)
{
	fmat3 lhs(2);
	fmat3 rhs(lhs);

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
}

TEST(fmat3, MoveConstructor)
{
	fmat3 lhs(2);
	fmat3 rhs(std::move(lhs));

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m02, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
	EXPECT_EQ(rhs.m12, 0);
	EXPECT_EQ(rhs.m20, 0);
	EXPECT_EQ(rhs.m21, 0);
	EXPECT_EQ(rhs.m22, 2);
}

TEST(fmat3, ComponentSet)
{
	fmat3 m;
	m.set(1, 2, 3, 4, 5, 6, 7, 8, 9);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(fmat3, ArraySet)
{
	f32 values[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	fmat3 m;
	m.set(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(fmat3, Equals)
{
	fmat3 lhs(1, 2, 3, 4, 5, 6, 7, 8, 9);
	fmat3 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(fmat3, NotEquals)
{
	fmat3 lhs(1, 3, 3, 4, 4, 6, 7, 8, 9);
	fmat3 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(fmat3, CopyAssign)
{
	fmat3 lhs;
	fmat3 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9);

	lhs = rhs;

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m02, 3);
	EXPECT_EQ(lhs.m10, 4);
	EXPECT_EQ(lhs.m11, 5);
	EXPECT_EQ(lhs.m12, 6);
	EXPECT_EQ(lhs.m20, 7);
	EXPECT_EQ(lhs.m21, 8);
	EXPECT_EQ(lhs.m22, 9);
}

TEST(fmat3, MoveAssign)
{
	fmat3 lhs;
	fmat3 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9);

	lhs = std::move(rhs);

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m02, 3);
	EXPECT_EQ(lhs.m10, 4);
	EXPECT_EQ(lhs.m11, 5);
	EXPECT_EQ(lhs.m12, 6);
	EXPECT_EQ(lhs.m20, 7);
	EXPECT_EQ(lhs.m21, 8);
	EXPECT_EQ(lhs.m22, 9);
}

TEST(fmat3, MatrixMultiplyOperator)
{
	fmat3 lhs(1, 2, 3, 4, 5, 6, 7, 8, 9);
	fmat3 rhs(9, 8, 7, 6, 5, 4, 3, 2, 1);

	lhs *= rhs;

	EXPECT_EQ(lhs.m00, 90);
	EXPECT_EQ(lhs.m01, 114);
	EXPECT_EQ(lhs.m02, 138);
	EXPECT_EQ(lhs.m10, 54);
	EXPECT_EQ(lhs.m11, 69);
	EXPECT_EQ(lhs.m12, 84);
	EXPECT_EQ(lhs.m20, 18);
	EXPECT_EQ(lhs.m21, 24);
	EXPECT_EQ(lhs.m22, 30);
}

TEST(fmat3, Identity)
{
	fmat3 m(2);
	m.identity();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 1);
}

TEST(fmat3, Transpose)
{
	fmat3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
	m.transpose();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 4);
	EXPECT_EQ(m.m02, 7);
	EXPECT_EQ(m.m10, 2);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 8);
	EXPECT_EQ(m.m20, 3);
	EXPECT_EQ(m.m21, 6);
	EXPECT_EQ(m.m22, 9);
}

TEST(fmat3, Invert)
{
	fmat3 m(1, 2, 2, 3, 2, 4, 2, 1, 5);
	m.invert();

	EXPECT_FLOAT_EQ(m.m00, -3.0f/5.0f);
	EXPECT_FLOAT_EQ(m.m01, 4.0f/5.0f);
	EXPECT_FLOAT_EQ(m.m02, -2.0f/5.0f);
	EXPECT_FLOAT_EQ(m.m10, 7.0f/10.0f);
	EXPECT_FLOAT_EQ(m.m11, -1.0f/10.0f);
	EXPECT_FLOAT_EQ(m.m12, -1.0f/5.0f);
	EXPECT_FLOAT_EQ(m.m20, 1.0f/10.0f);
	EXPECT_FLOAT_EQ(m.m21, -3.0f/10.0f);
	EXPECT_FLOAT_EQ(m.m22, 2.0f/5.0f);
}

TEST(fmat3, Negate)
{
	fmat3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
	m.negate();

	EXPECT_EQ(m.m00, -1);
	EXPECT_EQ(m.m01, -2);
	EXPECT_EQ(m.m02, -3);
	EXPECT_EQ(m.m10, -4);
	EXPECT_EQ(m.m11, -5);
	EXPECT_EQ(m.m12, -6);
	EXPECT_EQ(m.m20, -7);
	EXPECT_EQ(m.m21, -8);
	EXPECT_EQ(m.m22, -9);
}

TEST(fmat3, Determinant)
{
	fmat3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
	f32 d = m.determinant();

	EXPECT_EQ(d, 0);
}

// DMAT3 Tests

TEST(dmat3, DefaultConstructor)
{
	dmat3 m;

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 1);
}

TEST(dmat3, ComponentConstructor)
{
	dmat3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(dmat3, DiagonalConstructor)
{
	dmat3 m(2);

	EXPECT_EQ(m.m00, 2);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 2);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 2);
}

TEST(dmat3, ArrayConstructor)
{
	f64 values[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	dmat3 m(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(dmat3, ColumnConstructor)
{
	f64 col1[3] = {
		1, 2, 3
	};

	f64 col2[3] = {
		4, 5, 6
	};

	f64 col3[3] = {
		7, 8, 9
	};

	dmat3 m(col1, col2, col3);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(dmat3, CopyConstructor)
{
	dmat3 lhs(2);
	dmat3 rhs(lhs);

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
}

TEST(dmat3, MoveConstructor)
{
	dmat3 lhs(2);
	dmat3 rhs(std::move(lhs));

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m02, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
	EXPECT_EQ(rhs.m12, 0);
	EXPECT_EQ(rhs.m20, 0);
	EXPECT_EQ(rhs.m21, 0);
	EXPECT_EQ(rhs.m22, 2);
}

TEST(dmat3, ComponentSet)
{
	dmat3 m;
	m.set(1, 2, 3, 4, 5, 6, 7, 8, 9);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(dmat3, ArraySet)
{
	f64 values[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	dmat3 m;
	m.set(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m10, 4);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 6);
	EXPECT_EQ(m.m20, 7);
	EXPECT_EQ(m.m21, 8);
	EXPECT_EQ(m.m22, 9);
}

TEST(dmat3, Equals)
{
	dmat3 lhs(1, 2, 3, 4, 5, 6, 7, 8, 9);
	dmat3 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(dmat3, NotEquals)
{
	dmat3 lhs(1, 3, 3, 4, 4, 6, 7, 8, 9);
	dmat3 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(dmat3, CopyAssign)
{
	dmat3 lhs;
	dmat3 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9);

	lhs = rhs;

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m02, 3);
	EXPECT_EQ(lhs.m10, 4);
	EXPECT_EQ(lhs.m11, 5);
	EXPECT_EQ(lhs.m12, 6);
	EXPECT_EQ(lhs.m20, 7);
	EXPECT_EQ(lhs.m21, 8);
	EXPECT_EQ(lhs.m22, 9);
}

TEST(dmat3, MoveAssign)
{
	dmat3 lhs;
	dmat3 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9);

	lhs = std::move(rhs);

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m02, 3);
	EXPECT_EQ(lhs.m10, 4);
	EXPECT_EQ(lhs.m11, 5);
	EXPECT_EQ(lhs.m12, 6);
	EXPECT_EQ(lhs.m20, 7);
	EXPECT_EQ(lhs.m21, 8);
	EXPECT_EQ(lhs.m22, 9);
}

TEST(dmat3, MatrixMultiplyOperator)
{
	dmat3 lhs(1, 2, 3, 4, 5, 6, 7, 8, 9);
	dmat3 rhs(9, 8, 7, 6, 5, 4, 3, 2, 1);

	lhs *= rhs;

	EXPECT_EQ(lhs.m00, 90);
	EXPECT_EQ(lhs.m01, 114);
	EXPECT_EQ(lhs.m02, 138);
	EXPECT_EQ(lhs.m10, 54);
	EXPECT_EQ(lhs.m11, 69);
	EXPECT_EQ(lhs.m12, 84);
	EXPECT_EQ(lhs.m20, 18);
	EXPECT_EQ(lhs.m21, 24);
	EXPECT_EQ(lhs.m22, 30);
}

TEST(dmat3, Identity)
{
	dmat3 m(2);
	m.identity();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 1);
}

TEST(dmat3, Transpose)
{
	dmat3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
	m.transpose();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 4);
	EXPECT_EQ(m.m02, 7);
	EXPECT_EQ(m.m10, 2);
	EXPECT_EQ(m.m11, 5);
	EXPECT_EQ(m.m12, 8);
	EXPECT_EQ(m.m20, 3);
	EXPECT_EQ(m.m21, 6);
	EXPECT_EQ(m.m22, 9);
}

TEST(dmat3, Invert)
{
	dmat3 m(1, 2, 2, 3, 2, 4, 2, 1, 5);
	m.invert();

	EXPECT_FLOAT_EQ(m.m00, -3.0 / 5.0);
	EXPECT_FLOAT_EQ(m.m01, 4.0 / 5.0);
	EXPECT_FLOAT_EQ(m.m02, -2.0 / 5.0);
	EXPECT_FLOAT_EQ(m.m10, 7.0 / 10.0);
	EXPECT_FLOAT_EQ(m.m11, -1.0 / 10.0);
	EXPECT_FLOAT_EQ(m.m12, -1.0 / 5.0);
	EXPECT_FLOAT_EQ(m.m20, 1.0 / 10.0);
	EXPECT_FLOAT_EQ(m.m21, -3.0 / 10.0);
	EXPECT_FLOAT_EQ(m.m22, 2.0 / 5.0);
}

TEST(dmat3, Negate)
{
	dmat3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
	m.negate();

	EXPECT_EQ(m.m00, -1);
	EXPECT_EQ(m.m01, -2);
	EXPECT_EQ(m.m02, -3);
	EXPECT_EQ(m.m10, -4);
	EXPECT_EQ(m.m11, -5);
	EXPECT_EQ(m.m12, -6);
	EXPECT_EQ(m.m20, -7);
	EXPECT_EQ(m.m21, -8);
	EXPECT_EQ(m.m22, -9);
}

TEST(dmat3, Determinant)
{
	dmat3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
	f64 d = m.determinant();

	EXPECT_EQ(d, 0);
}

#include "mat4.h"

// FMAT4 Tests

TEST(fmat4, DefaultConstructor)
{
	fmat4 m;

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m03, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m13, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 1);
	EXPECT_EQ(m.m23, 0);
	EXPECT_EQ(m.m30, 0);
	EXPECT_EQ(m.m31, 0);
	EXPECT_EQ(m.m32, 0);
	EXPECT_EQ(m.m33, 1);
}

TEST(fmat4, ComponentConstructor)
{
	fmat4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(fmat4, DiagonalConstructor)
{
	fmat4 m(2);

	EXPECT_EQ(m.m00, 2);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m03, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 2);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m13, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 2);
	EXPECT_EQ(m.m23, 0);
	EXPECT_EQ(m.m30, 0);
	EXPECT_EQ(m.m31, 0);
	EXPECT_EQ(m.m32, 0);
	EXPECT_EQ(m.m33, 2);
}

TEST(fmat4, ArrayConstructor)
{
	f32 values[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
	};

	fmat4 m(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(fmat4, ColumnConstructor)
{
	f32 col1[4] = {
		1, 2, 3, 4
	};

	f32 col2[4] = {
		5, 6, 7, 8
	};

	f32 col3[4] = {
		9, 10, 11, 12
	};

	f32 col4[4] = {
		13, 14, 15, 16
	};

	fmat4 m(col1, col2, col3, col4);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(fmat4, CopyConstructor)
{
	fmat4 lhs(2);
	fmat4 rhs(lhs);

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m02, 0);
	EXPECT_EQ(rhs.m03, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
	EXPECT_EQ(rhs.m12, 0);
	EXPECT_EQ(rhs.m13, 0);
	EXPECT_EQ(rhs.m20, 0);
	EXPECT_EQ(rhs.m21, 0);
	EXPECT_EQ(rhs.m22, 2);
	EXPECT_EQ(rhs.m23, 0);
	EXPECT_EQ(rhs.m30, 0);
	EXPECT_EQ(rhs.m31, 0);
	EXPECT_EQ(rhs.m32, 0);
	EXPECT_EQ(rhs.m33, 2);
}

TEST(fmat4, MoveConstructor)
{
	fmat4 lhs(2);
	fmat4 rhs(std::move(lhs));

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m02, 0);
	EXPECT_EQ(rhs.m03, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
	EXPECT_EQ(rhs.m12, 0);
	EXPECT_EQ(rhs.m13, 0);
	EXPECT_EQ(rhs.m20, 0);
	EXPECT_EQ(rhs.m21, 0);
	EXPECT_EQ(rhs.m22, 2);
	EXPECT_EQ(rhs.m23, 0);
	EXPECT_EQ(rhs.m30, 0);
	EXPECT_EQ(rhs.m31, 0);
	EXPECT_EQ(rhs.m32, 0);
	EXPECT_EQ(rhs.m33, 2);
}

TEST(fmat4, ComponentSet)
{
	fmat4 m;
	m.set(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(fmat4, ArraySet)
{
	f32 values[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 ,12, 13, 14, 15, 16
	};

	fmat4 m;
	m.set(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(fmat4, Equals)
{
	fmat4 lhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	fmat4 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(fmat4, NotEquals)
{
	fmat4 lhs(1, 3, 3, 4, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	fmat4 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 11, 12, 13, 14, 15, 16);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(fmat4, CopyAssign)
{
	fmat4 lhs;
	fmat4 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	lhs = rhs;

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m02, 3);
	EXPECT_EQ(lhs.m03, 4);
	EXPECT_EQ(lhs.m10, 5);
	EXPECT_EQ(lhs.m11, 6);
	EXPECT_EQ(lhs.m12, 7);
	EXPECT_EQ(lhs.m13, 8);
	EXPECT_EQ(lhs.m20, 9);
	EXPECT_EQ(lhs.m21, 10);
	EXPECT_EQ(lhs.m22, 11);
	EXPECT_EQ(lhs.m23, 12);
	EXPECT_EQ(lhs.m30, 13);
	EXPECT_EQ(lhs.m31, 14);
	EXPECT_EQ(lhs.m32, 15);
	EXPECT_EQ(lhs.m33, 16);
}

TEST(fmat4, MoveAssign)
{
	fmat4 lhs;
	fmat4 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	lhs = std::move(rhs);

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m02, 3);
	EXPECT_EQ(lhs.m03, 4);
	EXPECT_EQ(lhs.m10, 5);
	EXPECT_EQ(lhs.m11, 6);
	EXPECT_EQ(lhs.m12, 7);
	EXPECT_EQ(lhs.m13, 8);
	EXPECT_EQ(lhs.m20, 9);
	EXPECT_EQ(lhs.m21, 10);
	EXPECT_EQ(lhs.m22, 11);
	EXPECT_EQ(lhs.m23, 12);
	EXPECT_EQ(lhs.m30, 13);
	EXPECT_EQ(lhs.m31, 14);
	EXPECT_EQ(lhs.m32, 15);
	EXPECT_EQ(lhs.m33, 16);
}

TEST(fmat4, MatrixMultiplyOperator)
{
	fmat4 lhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	fmat4 rhs(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);

	lhs *= rhs;

	EXPECT_EQ(lhs.m00, 386);
	EXPECT_EQ(lhs.m01, 444);
	EXPECT_EQ(lhs.m02, 502);
	EXPECT_EQ(lhs.m03, 560);
	EXPECT_EQ(lhs.m10, 274);
	EXPECT_EQ(lhs.m11, 316);
	EXPECT_EQ(lhs.m12, 358);
	EXPECT_EQ(lhs.m13, 400);
	EXPECT_EQ(lhs.m20, 162);
	EXPECT_EQ(lhs.m21, 188);
	EXPECT_EQ(lhs.m22, 214);
	EXPECT_EQ(lhs.m23, 240);
	EXPECT_EQ(lhs.m30, 50);
	EXPECT_EQ(lhs.m31, 60);
	EXPECT_EQ(lhs.m32, 70);
	EXPECT_EQ(lhs.m33, 80);
}

TEST(fmat4, Identity)
{
	fmat4 m(2);
	m.identity();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m03, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m13, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 1);
	EXPECT_EQ(m.m23, 0);
	EXPECT_EQ(m.m30, 0);
	EXPECT_EQ(m.m31, 0);
	EXPECT_EQ(m.m32, 0);
	EXPECT_EQ(m.m33, 1);
}

TEST(fmat4, Transpose)
{
	fmat4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	m.transpose();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 5);
	EXPECT_EQ(m.m02, 9);
	EXPECT_EQ(m.m03, 13);
	EXPECT_EQ(m.m10, 2);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 10);
	EXPECT_EQ(m.m13, 14);
	EXPECT_EQ(m.m20, 3);
	EXPECT_EQ(m.m21, 7);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 15);
	EXPECT_EQ(m.m30, 4);
	EXPECT_EQ(m.m31, 8);
	EXPECT_EQ(m.m32, 12);
	EXPECT_EQ(m.m33, 16);
}

TEST(fmat4, Invert)
{
	fmat4 m(0, 3, 0, 0, 2, 7, 0, 1, 8, 1, 1, 0, 6, 0, 2, 1);
	m.invert();

	EXPECT_EQ(m.m00, -1.0f/4.0f);
	EXPECT_EQ(m.m01, 1.0f/12.0f);
	EXPECT_EQ(m.m02, 1.0f/6.0f);
	EXPECT_EQ(m.m03, -1.0f/12.0f);
	EXPECT_EQ(m.m10, 1.0f/3.0f);
	EXPECT_EQ(m.m11, 0);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m13, 0);
	EXPECT_EQ(m.m20, 5.0f/3.0f);
	EXPECT_EQ(m.m21, -2.0f/3.0f);
	EXPECT_EQ(m.m22, -1.0f/3.0f);
	EXPECT_EQ(m.m23, 2.0f/3.0f);
	EXPECT_EQ(m.m30, -11.0f/6.0f);
	EXPECT_EQ(m.m31, 5.0f/6.0f);
	EXPECT_EQ(m.m32, -1.0f/3.0f);
	EXPECT_EQ(m.m33, 1.0f/6.0f);
}

TEST(fmat4, Negate)
{
	fmat4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	m.negate();

	EXPECT_EQ(m.m00, -1);
	EXPECT_EQ(m.m01, -2);
	EXPECT_EQ(m.m02, -3);
	EXPECT_EQ(m.m03, -4);
	EXPECT_EQ(m.m10, -5);
	EXPECT_EQ(m.m11, -6);
	EXPECT_EQ(m.m12, -7);
	EXPECT_EQ(m.m13, -8);
	EXPECT_EQ(m.m20, -9);
	EXPECT_EQ(m.m21, -10);
	EXPECT_EQ(m.m22, -11);
	EXPECT_EQ(m.m23, -12);
	EXPECT_EQ(m.m30, -13);
	EXPECT_EQ(m.m31, -14);
	EXPECT_EQ(m.m32, -15);
	EXPECT_EQ(m.m33, -16);
}

TEST(fmat4, Determinant)
{
	fmat4 m(0, 3, 0, 0, 2, 7, 0, 1, 8, 1, 1, 0, 6, 0, 2, 1);
	f32 d = m.determinant();

	EXPECT_EQ(d, -36);
}

// DMAT4 Tests

TEST(dmat4, DefaultConstructor)
{
	dmat4 m;

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m03, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m13, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 1);
	EXPECT_EQ(m.m23, 0);
	EXPECT_EQ(m.m30, 0);
	EXPECT_EQ(m.m31, 0);
	EXPECT_EQ(m.m32, 0);
	EXPECT_EQ(m.m33, 1);
}

TEST(dmat4, ComponentConstructor)
{
	dmat4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(dmat4, DiagonalConstructor)
{
	dmat4 m(2);

	EXPECT_EQ(m.m00, 2);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m03, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 2);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m13, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 2);
	EXPECT_EQ(m.m23, 0);
	EXPECT_EQ(m.m30, 0);
	EXPECT_EQ(m.m31, 0);
	EXPECT_EQ(m.m32, 0);
	EXPECT_EQ(m.m33, 2);
}

TEST(dmat4, ArrayConstructor)
{
	f64 values[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
	};

	dmat4 m(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(dmat4, ColumnConstructor)
{
	f64 col1[4] = {
		1, 2, 3, 4
	};

	f64 col2[4] = {
		5, 6, 7, 8
	};

	f64 col3[4] = {
		9, 10, 11, 12
	};

	f64 col4[4] = {
		13, 14, 15, 16
	};

	dmat4 m(col1, col2, col3, col4);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(dmat4, CopyConstructor)
{
	dmat4 lhs(2);
	dmat4 rhs(lhs);

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m02, 0);
	EXPECT_EQ(rhs.m03, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
	EXPECT_EQ(rhs.m12, 0);
	EXPECT_EQ(rhs.m13, 0);
	EXPECT_EQ(rhs.m20, 0);
	EXPECT_EQ(rhs.m21, 0);
	EXPECT_EQ(rhs.m22, 2);
	EXPECT_EQ(rhs.m23, 0);
	EXPECT_EQ(rhs.m30, 0);
	EXPECT_EQ(rhs.m31, 0);
	EXPECT_EQ(rhs.m32, 0);
	EXPECT_EQ(rhs.m33, 2);
}

TEST(dmat4, MoveConstructor)
{
	dmat4 lhs(2);
	dmat4 rhs(std::move(lhs));

	EXPECT_EQ(rhs.m00, 2);
	EXPECT_EQ(rhs.m01, 0);
	EXPECT_EQ(rhs.m02, 0);
	EXPECT_EQ(rhs.m03, 0);
	EXPECT_EQ(rhs.m10, 0);
	EXPECT_EQ(rhs.m11, 2);
	EXPECT_EQ(rhs.m12, 0);
	EXPECT_EQ(rhs.m13, 0);
	EXPECT_EQ(rhs.m20, 0);
	EXPECT_EQ(rhs.m21, 0);
	EXPECT_EQ(rhs.m22, 2);
	EXPECT_EQ(rhs.m23, 0);
	EXPECT_EQ(rhs.m30, 0);
	EXPECT_EQ(rhs.m31, 0);
	EXPECT_EQ(rhs.m32, 0);
	EXPECT_EQ(rhs.m33, 2);
}

TEST(dmat4, ComponentSet)
{
	dmat4 m;
	m.set(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(dmat4, ArraySet)
{
	f64 values[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 ,12, 13, 14, 15, 16
	};

	dmat4 m;
	m.set(values);

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 2);
	EXPECT_EQ(m.m02, 3);
	EXPECT_EQ(m.m03, 4);
	EXPECT_EQ(m.m10, 5);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 7);
	EXPECT_EQ(m.m13, 8);
	EXPECT_EQ(m.m20, 9);
	EXPECT_EQ(m.m21, 10);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 12);
	EXPECT_EQ(m.m30, 13);
	EXPECT_EQ(m.m31, 14);
	EXPECT_EQ(m.m32, 15);
	EXPECT_EQ(m.m33, 16);
}

TEST(dmat4, Equals)
{
	dmat4 lhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	dmat4 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	ASSERT_TRUE(lhs == rhs);
	ASSERT_FALSE(lhs != rhs);

	EXPECT_EQ(lhs, rhs);
}

TEST(dmat4, NotEquals)
{
	dmat4 lhs(1, 3, 3, 4, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	dmat4 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 11, 12, 13, 14, 15, 16);

	ASSERT_TRUE(lhs != rhs);
	ASSERT_FALSE(lhs == rhs);

	EXPECT_NE(lhs, rhs);
}

TEST(dmat4, CopyAssign)
{
	dmat4 lhs;
	dmat4 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	lhs = rhs;

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m02, 3);
	EXPECT_EQ(lhs.m03, 4);
	EXPECT_EQ(lhs.m10, 5);
	EXPECT_EQ(lhs.m11, 6);
	EXPECT_EQ(lhs.m12, 7);
	EXPECT_EQ(lhs.m13, 8);
	EXPECT_EQ(lhs.m20, 9);
	EXPECT_EQ(lhs.m21, 10);
	EXPECT_EQ(lhs.m22, 11);
	EXPECT_EQ(lhs.m23, 12);
	EXPECT_EQ(lhs.m30, 13);
	EXPECT_EQ(lhs.m31, 14);
	EXPECT_EQ(lhs.m32, 15);
	EXPECT_EQ(lhs.m33, 16);
}

TEST(dmat4, MoveAssign)
{
	dmat4 lhs;
	dmat4 rhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	lhs = std::move(rhs);

	EXPECT_EQ(lhs.m00, 1);
	EXPECT_EQ(lhs.m01, 2);
	EXPECT_EQ(lhs.m02, 3);
	EXPECT_EQ(lhs.m03, 4);
	EXPECT_EQ(lhs.m10, 5);
	EXPECT_EQ(lhs.m11, 6);
	EXPECT_EQ(lhs.m12, 7);
	EXPECT_EQ(lhs.m13, 8);
	EXPECT_EQ(lhs.m20, 9);
	EXPECT_EQ(lhs.m21, 10);
	EXPECT_EQ(lhs.m22, 11);
	EXPECT_EQ(lhs.m23, 12);
	EXPECT_EQ(lhs.m30, 13);
	EXPECT_EQ(lhs.m31, 14);
	EXPECT_EQ(lhs.m32, 15);
	EXPECT_EQ(lhs.m33, 16);
}

TEST(dmat4, MatrixMultiplyOperator)
{
	dmat4 lhs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	dmat4 rhs(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);

	lhs *= rhs;

	EXPECT_EQ(lhs.m00, 386);
	EXPECT_EQ(lhs.m01, 444);
	EXPECT_EQ(lhs.m02, 502);
	EXPECT_EQ(lhs.m03, 560);
	EXPECT_EQ(lhs.m10, 274);
	EXPECT_EQ(lhs.m11, 316);
	EXPECT_EQ(lhs.m12, 358);
	EXPECT_EQ(lhs.m13, 400);
	EXPECT_EQ(lhs.m20, 162);
	EXPECT_EQ(lhs.m21, 188);
	EXPECT_EQ(lhs.m22, 214);
	EXPECT_EQ(lhs.m23, 240);
	EXPECT_EQ(lhs.m30, 50);
	EXPECT_EQ(lhs.m31, 60);
	EXPECT_EQ(lhs.m32, 70);
	EXPECT_EQ(lhs.m33, 80);
}

TEST(dmat4, Identity)
{
	dmat4 m(2);
	m.identity();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 0);
	EXPECT_EQ(m.m02, 0);
	EXPECT_EQ(m.m03, 0);
	EXPECT_EQ(m.m10, 0);
	EXPECT_EQ(m.m11, 1);
	EXPECT_EQ(m.m12, 0);
	EXPECT_EQ(m.m13, 0);
	EXPECT_EQ(m.m20, 0);
	EXPECT_EQ(m.m21, 0);
	EXPECT_EQ(m.m22, 1);
	EXPECT_EQ(m.m23, 0);
	EXPECT_EQ(m.m30, 0);
	EXPECT_EQ(m.m31, 0);
	EXPECT_EQ(m.m32, 0);
	EXPECT_EQ(m.m33, 1);
}

TEST(dmat4, Transpose)
{
	dmat4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	m.transpose();

	EXPECT_EQ(m.m00, 1);
	EXPECT_EQ(m.m01, 5);
	EXPECT_EQ(m.m02, 9);
	EXPECT_EQ(m.m03, 13);
	EXPECT_EQ(m.m10, 2);
	EXPECT_EQ(m.m11, 6);
	EXPECT_EQ(m.m12, 10);
	EXPECT_EQ(m.m13, 14);
	EXPECT_EQ(m.m20, 3);
	EXPECT_EQ(m.m21, 7);
	EXPECT_EQ(m.m22, 11);
	EXPECT_EQ(m.m23, 15);
	EXPECT_EQ(m.m30, 4);
	EXPECT_EQ(m.m31, 8);
	EXPECT_EQ(m.m32, 12);
	EXPECT_EQ(m.m33, 16);
}

TEST(dmat4, Invert)
{
	dmat4 m(0, 3, 0, 0, 2, 7, 0, 1, 8, 1, 1, 0, 6, 0, 2, 1);
	m.invert();

	EXPECT_FLOAT_EQ(m.m00, -1.0 / 4.0);
	EXPECT_FLOAT_EQ(m.m01, 1.0 / 12.0);
	EXPECT_FLOAT_EQ(m.m02, 1.0 / 6.0);
	EXPECT_FLOAT_EQ(m.m03, -1.0 / 12.0);
	EXPECT_FLOAT_EQ(m.m10, 1.0 / 3.0);
	EXPECT_FLOAT_EQ(m.m11, 0);
	EXPECT_FLOAT_EQ(m.m12, 0);
	EXPECT_FLOAT_EQ(m.m13, 0);
	EXPECT_FLOAT_EQ(m.m20, 5.0 / 3.0);
	EXPECT_FLOAT_EQ(m.m21, -2.0 / 3.0);
	EXPECT_FLOAT_EQ(m.m22, -1.0 / 3.0);
	EXPECT_FLOAT_EQ(m.m23, 2.0 / 3.0);
	EXPECT_FLOAT_EQ(m.m30, -11.0 / 6.0);
	EXPECT_FLOAT_EQ(m.m31, 5.0 / 6.0);
	EXPECT_FLOAT_EQ(m.m32, -1.0 / 3.0);
	EXPECT_FLOAT_EQ(m.m33, 1.0 / 6.0);
}

TEST(dmat4, Negate)
{
	dmat4 m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	m.negate();

	EXPECT_EQ(m.m00, -1);
	EXPECT_EQ(m.m01, -2);
	EXPECT_EQ(m.m02, -3);
	EXPECT_EQ(m.m03, -4);
	EXPECT_EQ(m.m10, -5);
	EXPECT_EQ(m.m11, -6);
	EXPECT_EQ(m.m12, -7);
	EXPECT_EQ(m.m13, -8);
	EXPECT_EQ(m.m20, -9);
	EXPECT_EQ(m.m21, -10);
	EXPECT_EQ(m.m22, -11);
	EXPECT_EQ(m.m23, -12);
	EXPECT_EQ(m.m30, -13);
	EXPECT_EQ(m.m31, -14);
	EXPECT_EQ(m.m32, -15);
	EXPECT_EQ(m.m33, -16);
}

TEST(dmat4, Determinant)
{
	dmat4 m(0, 3, 0, 0, 2, 7, 0, 1, 8, 1, 1, 0, 6, 0, 2, 1);
	f64 d = m.determinant();

	EXPECT_EQ(d, -36);
}