#pragma once

#include <cassert>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <limits>

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

  Vector(T x_ = 0, T y_ = 0, T z_ = 0) : x{x_}, y{y_}, z{z_} {}

  // --------------------------------------------------------------------------

  T& operator[](std::size_t i) { return data[i]; }
  const T& operator[](std::size_t i) const { return data[i]; }
};

// ----------------------------------------------------------------------------

using Vec3f = Vector<3, float>;
using Vec3d = Vector<3, double>;

// Hide the implementation internals.
template<typename T>
constexpr T epsilon() {
  // Use a simplified version of a solution because it should be sufficient
  // enough for the given task at hand.
  // https://stackoverflow.com/questions/4915462/how-should-i-do-floating-point-comparison
  return std::numeric_limits<T>::epsilon();
}

// ----------------------------------------------------------------------------

template <std::size_t N, Scalar T, typename Derived>
T dot(const VectorBase<N, T, Derived>& a, const VectorBase<N, T, Derived>& b) {
  const Derived& da{static_cast<const Derived&>(a)};
  const Derived& db{static_cast<const Derived&>(b)};

  T sum{0};

  for (std::size_t i{0}; i < N; ++i) {
    sum += da[i] * db[i];
  }

  return sum;
}

template <std::size_t N, Scalar T, typename Derived>
auto length(const VectorBase<N, T, Derived>& a) -> decltype(std::sqrt(T{})) {
  const Derived& da {static_cast<const Derived&>(a)};

  T sum{0};

  for (std::size_t i{0}; i < N; ++i) {
    sum += da[i] * da[i];
  }

  return std::sqrt(sum);
}

template <std::size_t N, Scalar T, typename Derived>
auto distance(const VectorBase<N, T, Derived>& a,
              const VectorBase<N, T, Derived>& b) {
  const Derived& da {static_cast<const Derived&>(a)};
  const Derived& db {static_cast<const Derived&>(b)};

  return length(db - da);
}

template<std::size_t N, std::floating_point T, typename Derived>
Derived normalize(const VectorBase<N, T, Derived>& a) {
  const Derived& da{static_cast<const Derived&>(a)};

  auto len{length(da)};

  return da * (T{1} / static_cast<T>(len));
}

template <Scalar T, typename Derived>
Derived cross(const VectorBase<3, T, Derived>& a,
              const VectorBase<3, T, Derived>& b) {
  const Derived& da{static_cast<const Derived&>(a)};
  const Derived& db{static_cast<const Derived&>(b)};

  Derived result;

  result[0] = da[1] * db[2] - da[2] * db[1];
  result[1] = da[2] * db[0] - da[0] * db[2];
  result[2] = da[0] * db[1] - da[1] * db[0];

  return result;
}

}  // namespace RubypointTask
