#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "rubypoint_task/rubypoint_task.h"

namespace App {

namespace rt = RubypointTask;

struct Segment {
  rt::Vec3d p0;
  rt::Vec3d p1;
};

struct Segments {
  Segment a;
  Segment b;
};

std::pair<rt::Vec3d, rt::Vec3d> ComputeClosestPoints(const Segments& segments) {
  const Segment& segmentA = segments.a;
  const Segment& segmentB = segments.b;

  const rt::Vec3d u{segmentA.p1 - segmentA.p0};
  const rt::Vec3d v{segmentB.p1 - segmentB.p0};

  const rt::Vec3d w0{segmentA.p0 - segmentB.p0};

  const auto a{rt::dot(u, u)};
  const auto b{rt::dot(u, v)};
  const auto c{rt::dot(v, v)};
  const auto d{rt::dot(u, w0)};
  const auto e{rt::dot(v, w0)};

  const auto D{b * b - a * c};
  const auto Ds{b * d - a * e};

  if (abs(D) < rt::epsilon<double>()) {
    throw std::runtime_error("The two segments are parallel!");
  }

  // In theory, this clamping may still produce incorrect results. There is no
  // guarantee that `l` will fall within a segment. Ideally, we would check, if
  // a parameter is within a segment, before and after projection. It is an
  // iterative process, which we can continue indefinitely, but in this case,
  // this solution is good enough.
  const auto sInit{std::clamp(Ds / D, 0.0, 1.0)};
  const auto k{std::clamp((sInit * b - d) / a, 0.0, 1.0)};
  const auto l{std::clamp((k * b + e) / c, 0.0, 1.0)};

  const auto W{segmentA.p0 + k * u};
  const auto Q{segmentB.p0 + l * v};

  return {W, Q};
}

bool intersects(const Segments& segments) {
  try {
    const constexpr double SATISFYING_ENOUGH_TRESHOLD{0.05};

    const auto point{ComputeClosestPoints(segments)};
    if (std::abs(rt::distance(point.first, point.second)) <
        SATISFYING_ENOUGH_TRESHOLD) {
      return true;
    }
    return false;
  } catch (...) {
    return false;
  }
}

std::string StrVec3d(const rt::Vec3d& vec, const std::string msg) {
  return msg + "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) +
         ", " + std::to_string(vec.z) + ")";
}

void RunSample(const Segments& segments, const std::string &title) {
  try {
    const auto result{ComputeClosestPoints(segments)};

    std::cout << "------\n"
              << title
              << StrVec3d(result.first, "First: ") << "\n"
              << StrVec3d(result.second, "Second: ") << "\n"
              << "Distance: " << rt::distance(result.first, result.second)
              << "\nIntersects: " << (intersects(segments) ? "True" : "False")
              << "\n------\n";
  } catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << "\n";
  }
}

}  // namespace App
