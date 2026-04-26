#include "rubypoint_task/rubypoint_task.h"

int main() {
  RubypointTask::Vec3f a_0;
  RubypointTask::Vec3f a_1;
  auto r_0{a_1 - a_0};
  auto r_1{3.0f * a_0};
  auto r_2{a_0 * 3.0f};
  std::cout << "Distance: "
            << RubypointTask::distance(RubypointTask::Vec3f{1.0f, 1.0f, 0.0f},
                                       RubypointTask::Vec3f{3.0f, 3.0f, 0.0f})
            << "\n";

  return 0;
}
