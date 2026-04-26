#include "rubypoint_task/rubypoint_task.h"

#include <cmath>

#include "gtest/gtest.h"

// Ensure operator overloads work correctly

namespace SetupTest {

template <std::size_t N, typename T>
struct Foo : RubypointTask::VectorBase<N, T, Foo<N, T>> {
  T data[N];

  Foo() : data{} {}

  template <typename... Args>
  Foo(Args... args) : data{static_cast<T>(args)...} {
    static_assert(sizeof...(Args) == N, "Number of arguments must match N!");
  }

  T& operator[](std::size_t i) { return data[i]; }
  const T& operator[](std::size_t i) const { return data[i]; }
};

}  // namespace SetupTest

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Inheritance, 3D
// ----------------------------------------------------------------------------

TEST(VectorBase, _3D_Inheritance_Works) {
  // Arrange
  SetupTest::Foo<3, float> a;
  SetupTest::Foo<3, float> b;

  a[0] = 1.0f;
  a[1] = 2.0f;
  a[2] = 3.0f;
  b[0] = 4.0f;
  b[1] = 5.0f;
  b[2] = 6.0f;

  // Act
  auto r{a + b};

  // Asset
  EXPECT_FLOAT_EQ(r[0], 5.0f);
  EXPECT_FLOAT_EQ(r[1], 7.0f);
  EXPECT_FLOAT_EQ(r[2], 9.0f);
}

TEST(VectorBase, _3D_Accepts_Double) {
  // Arrange
  SetupTest::Foo<3, int> a;
  SetupTest::Foo<3, int> b;

  a[0] = 1.0;
  a[1] = 2.0;
  a[2] = 3.0;
  b[0] = 4.0;
  b[1] = 5.0;
  b[2] = 6.0;

  // Act
  auto r{a + b};

  // Asset
  EXPECT_DOUBLE_EQ(r[0], 5.0);
  EXPECT_DOUBLE_EQ(r[1], 7.0);
  EXPECT_DOUBLE_EQ(r[2], 9.0);
}

// ----------------------------------------------------------------------------
// Inheritance, 2D
// ----------------------------------------------------------------------------

TEST(VectorBase, _2D_Inheritance_Works) {
  // Arrange
  SetupTest::Foo<2, float> a;
  SetupTest::Foo<2, float> b;

  a[0] = 1.0f;
  a[1] = 2.0f;
  b[0] = 3.0f;
  b[1] = 4.0f;

  // Act
  auto r{a + b};

  // Asset
  EXPECT_FLOAT_EQ(r[0], 4.0f);
  EXPECT_FLOAT_EQ(r[1], 6.0f);
}

TEST(VectorBase, _2D_Accepts_Integer) {
  // Arrange
  SetupTest::Foo<2, int> a;
  SetupTest::Foo<2, int> b;

  a[0] = 1;
  a[1] = 2;
  b[0] = 3;
  b[1] = 4;

  // Act
  auto r{a + b};

  // Asset
  EXPECT_EQ(r[0], 4);
  EXPECT_EQ(r[1], 6);
}

// ----------------------------------------------------------------------------
// Dot product
// ----------------------------------------------------------------------------

TEST(Dot_Product, GeneralCase) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 2.0, 3.0};
  SetupTest::Foo<3, double> b{4.0, 5.0, 6.0};

  // Act
  auto r{RubypointTask::dot(a, b)};

  // Assert
  EXPECT_DOUBLE_EQ(r, 32.0);
}

TEST(Dot_Product, ParallelVectors) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 0.0, 0.0};
  SetupTest::Foo<3, double> b{2.0, 0.0, 0.0};

  // Act
  auto r{RubypointTask::dot(a, b)};

  // Assert
  EXPECT_DOUBLE_EQ(r, 2.0);
}

TEST(Dot_Product, PerpendicularVectors) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 0.0, 0.0};
  SetupTest::Foo<3, double> b{0.0, 1.0, 0.0};

  // Act
  auto r{RubypointTask::dot(a, b)};

  // Assert
  EXPECT_DOUBLE_EQ(r, 0.0);
}

// ----------------------------------------------------------------------------
// Cross product
// ----------------------------------------------------------------------------

TEST(Cross_Product, X_Cross_Y_Is_Z) {
  // Arrange
  SetupTest::Foo<3, double> x{1.0, 0.0, 0.0};
  SetupTest::Foo<3, double> y{0.0, 1.0, 0.0};

  // Act
  auto r{RubypointTask::cross(x, y)};

  // Assert
  EXPECT_DOUBLE_EQ(r[0], 0.0);
  EXPECT_DOUBLE_EQ(r[1], 0.0);
  EXPECT_DOUBLE_EQ(r[2], 1.0);
}

TEST(Cross_Product, Anti_Commutative) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 2.0, 3.0};
  SetupTest::Foo<3, double> b{4.0, 5.0, 6.0};

  // Act
  auto ab{RubypointTask::cross(a, b)};
  auto ba{RubypointTask::cross(b, a)};

  // Assert
  EXPECT_DOUBLE_EQ(ab[0], -ba[0]);
  EXPECT_DOUBLE_EQ(ab[1], -ba[1]);
  EXPECT_DOUBLE_EQ(ab[2], -ba[2]);
}

TEST(Cross_Product, Parallel_Vectors_Is_Zero) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 0.0, 0.0};
  SetupTest::Foo<3, double> b{2.0, 0.0, 0.0};

  // Act
  auto r{RubypointTask::cross(a, b)};

  // Assert
  EXPECT_DOUBLE_EQ(r[0], 0.0);
  EXPECT_DOUBLE_EQ(r[1], 0.0);
  EXPECT_DOUBLE_EQ(r[2], 0.0);
}

// ----------------------------------------------------------------------------
// Length
// ----------------------------------------------------------------------------

TEST(Length, Unit_Vector) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 0.0, 0.0};

  // Act
  auto r{RubypointTask::length(a)};

  // Assert
  EXPECT_DOUBLE_EQ(r, 1.0);
}

TEST(Length, General_Case) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 1.0, 0.0};

  // Act
  auto r{RubypointTask::length(a)};

  // Assert
  EXPECT_DOUBLE_EQ(r, std::sqrt(2.0));
}

TEST(Length, Zero_Vector) {
  // Arrange
  SetupTest::Foo<3, double> a{0.0, 0.0, 0.0};

  // Act
  auto r{RubypointTask::length(a)};

  // Assert
  EXPECT_DOUBLE_EQ(r, 0.0);
}

// ----------------------------------------------------------------------------
// Distance
// ----------------------------------------------------------------------------

TEST(Distance, Known_Points) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 1.0, 0.0};
  SetupTest::Foo<3, double> b{3.0, 3.0, 0.0};

  // Act
  auto r{RubypointTask::distance(a, b)};

  // Assert
  EXPECT_DOUBLE_EQ(r, std::sqrt(8.0));
}

TEST(Distance, Same_Point_Is_Zero) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 1.0, 0.0};

  // Act
  auto r{RubypointTask::distance(a, a)};

  // Assert
  EXPECT_DOUBLE_EQ(r, 0.0);
}

TEST(Distance, Is_Symmetric) {
  // Arrange
  SetupTest::Foo<3, double> a{1.0, 0.0, 0.0};
  SetupTest::Foo<3, double> b{4.0, 0.0, 0.0};

  // Act
  auto ab{RubypointTask::distance(a, b)};
  auto ba{RubypointTask::distance(b, a)};

  // Assert
  EXPECT_DOUBLE_EQ(ab, ba);
}
