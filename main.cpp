#include <concepts>
#include <cstddef>
#include <iostream>
#include <utility>

namespace RubypointTask {
  template <typename T>
  concept Scalar = std::is_arithmetic_v<T>;

  template<std::size_t N, Scalar T>
  struct Vector {
    T data[N];

    T& operator[](std::size_t i) { return data[i]; }
    const T& operator[](std::size_t i) const { return data[i]; }
  };

  template<Scalar T>
  struct Vector<3, T> {
    union {
      T data[3];
      struct { T x; T y; T z; }
    }

    T& operator[](std::size_t i) { return data[i]; }
  };

  using Vec3f = Vector<float>;

  // Use GLSL/GLM namings
  template <Scalar T> class Vec3 {
    // Ensure default value initialization using {}
    T m_x{};
    T m_y{};
    T m_z{};

  public:
    Vec3() = default;

    explicit Vec3(T value) : m_x{ value }, m_y{ value }, m_z{ value } {}

    Vec3(T x, T y, T z) : m_x{ x }, m_y{ y }, m_z{ z } {}

    // TODO: +=, -=, *=, /=
    // TODO: Add friend operator overload for scalar * Vec3{}

    Vec3& operator+=(const Vec3& other) {
      m_x += other.m_x;
      m_y += other.m_y;
      m_z += other.m_z;

      return *this;
    }

    friend Vec3 operator+(Vec3 lhs, const Vec3& rhs) {
      lhs += rhs;

      return lhs;
    }

    Vec3& operator-=(const Vec3& other) {
      m_x -= other.m_x;
      m_y -= other.m_y;
      m_z -= other.m_z;

      return *this;
    }

    friend Vec3 operator-(Vec3 lhs, const Vec3& rhs) {
      lhs -= rhs;

      return lhs;
    }

    Vec3& operator*=(const Vec3& other) {
      m_x *= other.m_x;
      m_y *= other.m_y;
      m_z *= other.m_z;

      return *this;
    }

    friend Vec3 operator*(Vec3 lhs, const Vec3& rhs) {
      lhs *= rhs;

      return lhs;
    }

    friend Vec3 operator*(T s, const Vec3& v) {
      //
    }

    friend Vec3 operator*(const Vec3& v, T s) {
      //
    }

    Vec3& operator/=(const Vec3& other) {
      m_x /= other.m_x;
      m_y /= other.m_y;
      m_z /= other.m_z;

      return *this;
    }

    friend Vec3 operator/(Vec3 lhs, const Vec3& rhs) {
      lhs /= rhs;

      return lhs;
    }
  };

  using fVec3 = Vec3<float>;

} // namespace RubypointTask

int main() {
  RubypointTask::fVec3 a_0;
  RubypointTask::fVec3 a_1;
  auto r_0{ a_1 - a_0 };
  auto r_1{ 3.0f * a_0 };
  auto r_2{ a_0 * 3.0f };

  std::cout << "hello world\n";
  return 0;
}
