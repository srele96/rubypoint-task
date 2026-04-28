#pragma once

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

std::pair<rt::Vec3d, rt::Vec3d> ComputeClosestPoints(const Segments& segments);

bool intersects(const Segments& segments);

std::string StrVec3d(const rt::Vec3d& vec, const std::string msg);

void RunSample(const Segments& segments, const std::string& title);

}  // namespace App
