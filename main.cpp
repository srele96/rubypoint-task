#include <cmath>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <utility>

namespace RubypointTask {

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

// We need vector members to be packed sequentially in memory. This allows CPU
// and GPU efficiency, as GPU is often optimized for 16 bit alignment.
template <std::size_t N, Scalar T>
struct Vector {
  T data[N];

  T& operator[](std::size_t i) { return data[i]; }
  const T& operator[](std::size_t i) const { return data[i]; }
};

// I made the Vector class as generic as possible (but not more than necessary),
// even though the task requirements specifically say the computation is in 3D
// space. Vector should be N dimensional container of specialized scalar types.
template <Scalar T>
struct Vector<3, T> {
  // Allows access to each member for this specialization in a more clean way.
  union {
    T data[3];

    struct {
      T x;
      T y;
      T z;
    };
  };

  explicit Vector(T x_ = 0, T y_ = 0, T z_ = 0) : x{x_}, y{y_}, z{z_} {}

  // --------------------------------------------------------------------------

  T& operator[](std::size_t i) { return data[i]; }
  const T& operator[](std::size_t i) const { return data[i]; }

  // --------------------------------------------------------------------------

  Vector operator+(const Vector& o) const {
    return Vector{x + o.x, y + o.y, z + o.z};
  }

  Vector operator-(const Vector& o) const {
    return Vector{x - o.x, y - o.y, z - o.z};
  }

  Vector operator*(const Vector& o) const {
    return Vector{x * o.x, y * o.y, z * o.z};
  }

  Vector operator/(const Vector& o) const {
    return Vector{x / o.x, y / o.y, z / o.z};
  }

  // --------------------------------------------------------------------------

  Vector& operator+=(const Vector& o) { return *this = *this + o; }

  Vector& operator-=(const Vector& o) { return *this = *this - o; }

  Vector& operator*=(const Vector& o) { return *this = *this * o; }

  Vector& operator/=(const Vector& o) { return *this = *this / o; }

  Vector operator+(T s) const { return Vector{x + s, y + s, z + s}; }

  // --------------------------------------------------------------------------

  friend Vector operator+(T s, const Vector& v) { return v + s; }

  Vector operator-(T s) const { return Vector{x - s, y - s, z - s}; }

  friend Vector operator-(T s, const Vector& v) {
    return Vector{s - v.x, s - v.y, s - v.z};
  }

  Vector operator*(T s) const { return Vector{x * s, y * s, z * s}; }

  friend Vector operator*(T s, const Vector& v) { return v * s; }

  Vector operator/(T s) const { return Vector{x / s, y / s, z / s}; }

  friend Vector operator/(T s, const Vector& v) {
    return Vector{s / v.x, s / v.y, s / v.z};
  }
};

// ----------------------------------------------------------------------------

using Vec3f = Vector<3, float>;

// ----------------------------------------------------------------------------

template <std::size_t N, Scalar T>
T dot(const Vector<N, T>& a, const Vector<N, T>& b) {
  T sum{0};

  for (std::size_t i{0}; i < N; ++i) {
    sum += a[i] * b[i];
  }

  return sum;
}

template <std::size_t N, Scalar T>
T length(const Vector<N, T>& a) {
  T sum{0};

  for (std::size_t i{0}; i < N; ++i) {
    sum += a[i] * a[i];
  }

  return std::sqrt(sum);
}

template <Scalar T>
Vector<3, T> cross(const Vector<3, T>& a, const Vector<3, T>& b) {
  return Vector<3, T>{
      a.y * b.z - a.z * b.y,  //
      a.z * b.x - a.x * b.z,  //
      a.x * b.y - a.y * b.x   //
  };
}

}  // namespace RubypointTask

int main() {
  RubypointTask::Vec3f a_0;
  RubypointTask::Vec3f a_1;
  auto r_0{a_1 - a_0};
  auto r_1{3.0f * a_0};
  auto r_2{a_0 * 3.0f};

  std::cout << "hello world\n";
  return 0;
}
