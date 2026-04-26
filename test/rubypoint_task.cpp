#include "rubypoint_task/rubypoint_task.h"

#include "gtest/gtest.h"

// Ensures `double` precision data type works
// Ensures anonymous union can access members as named members
// Ensures access of members via [] notation
// Ensure inheritance works
// Ensure data is initialized correctly
// Ensure vector base accepts scalar data types
// Ensure operator overloads work correctly
// Ensure dot product works correctly
// Ensure cross product works correctly
// Ensure length works correctly
// Ensure distance works correctly

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
  SetupTest::Foo<3, double> a{1.0, 2.0, 3.0};
  SetupTest::Foo<3, double> b{4.0, 5.0, 6.0};

  EXPECT_DOUBLE_EQ(RubypointTask::dot(a, b), 32.0);
}

TEST(Dot_Product, ParallelVectors) {
  SetupTest::Foo<3, double> a{1.0, 0.0, 0.0};
  SetupTest::Foo<3, double> b{2.0, 0.0, 0.0};

  EXPECT_DOUBLE_EQ(RubypointTask::dot(a, b), 2.0);
}

TEST(Dot_Product, PerpendicularVectors) {
  SetupTest::Foo<3, double> a{1.0, 0.0, 0.0};
  SetupTest::Foo<3, double> b{0.0, 1.0, 0.0};

  EXPECT_DOUBLE_EQ(RubypointTask::dot(a, b), 0.0);
}

// ----------------------------------------------------------------------------
// Cross product
// ----------------------------------------------------------------------------

TEST(Cross_Product, Something) {
  //
}

// ----------------------------------------------------------------------------
// Length
// ----------------------------------------------------------------------------

TEST(Cross_Product, Something) {
  //
}
