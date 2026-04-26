#pragma once

#include <cmath>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <utility>
#include <cstddef>

namespace RubypointTask {

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

// Allows reuse of operator overloads at compile time
// https://en.cppreference.com/cpp/language/crtp
template <std::size_t N, Scalar T, typename Derived>
struct VectorBase {
  Derived& self() { return static_cast<Derived&>(*this); }
  const Derived& self() const { return static_cast<const Derived&>(*this); }

  // --------------------------------------------------------------------------

  Derived operator+(const Derived& o) const {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = self()[i] + o[i];
    }
    return result;
  }

  Derived operator-(const Derived& o) const {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = self()[i] - o[i];
    }
    return result;
  }

  Derived operator*(const Derived& o) const {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = self()[i] * o[i];
    }
    return result;
  }

  Derived operator/(const Derived& o) const {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = self()[i] / o[i];
    }
    return result;
  }

  // --------------------------------------------------------------------------

  Derived& operator+=(const Derived& o) { return self() = self() + o; }

  Derived& operator-=(const Derived& o) { return self() = self() - o; }

  Derived& operator*=(const Derived& o) { return self() = self() * o; }

  Derived& operator/=(const Derived& o) { return self() = self() / o; }

  // --------------------------------------------------------------------------

  Derived operator+(T s) const {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = self()[i] + s;
    }
    return result;
  }

  Derived operator-(T s) const {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = self()[i] - s;
    }
    return result;
  }

  Derived operator*(T s) const {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = self()[i] * s;
    }
    return result;
  }

  Derived operator/(T s) const {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = self()[i] / s;
    }
    return result;
  }

  // --------------------------------------------------------------------------

  friend Derived operator+(T s, const Derived& v) { return v + s; }

  friend Derived operator-(T s, const Derived& v) {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = s - v[i];
    }
    return result;
  }

  friend Derived operator*(T s, const Derived& v) { return v * s; }

  friend Derived operator/(T s, const Derived& v) {
    Derived result;
    for (std::size_t i{0}; i < N; ++i) {
      result[i] = s / v[i];
    }
    return result;
  }
};

// We need vector members to be packed sequentially in memory. This allows CPU
// and GPU efficiency, as GPU is often optimized for 16 bit alignment.
template <std::size_t N, Scalar T>
struct Vector : VectorBase<N, T, Vector<N, T>> {
  T data[N];

  Vector() : data{} {}

  T& operator[](std::size_t i) { return data[i]; }
  const T& operator[](std::size_t i) const { return data[i]; }
};

// Template specialization of 3D vector, which allows extension to N dimensional
// vector specialization.
//
// I made the Vector class as generic as possible (but not more than necessary),
// even though the task requirements specifically say the computation is in 3D
// space. Vector should be N dimensional container of specialized scalar types.
template <Scalar T>
struct Vector<3, T> : VectorBase<3, T, Vector<3, T>> {
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

template <std::size_t N, Scalar T>
T distance(const Vector<N, T>& a, const Vector<N, T>& b) {
  return length(b - a);
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
