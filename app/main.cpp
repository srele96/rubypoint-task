#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "app.h"
#include "rubypoint_task/rubypoint_task.h"

namespace rt = RubypointTask;

int main() {
  {
    std::cout << "Distance: "
              << rt::distance(rt::Vec3f{1.0f, 1.0f, 0.0f},
                              rt::Vec3f{3.0f, 3.0f, 0.0f})
              << "\n";
  }

  // Input coordinates were first configured and checked visually in the desmos
  // graph below, and then used as inputs.
  //
  // https://www.desmos.com/3d/txxmz6pgxy

  {
    const rt::Vec3d A0{2.0, 1.0, 1.0};
    const rt::Vec3d A1{-1, 1.0, -0.85};
    const rt::Vec3d B0{0.0, 1.0, 1.0};
    const rt::Vec3d B1{-1.0, 2.0, 2.0};

    const App::Segment segmentA{.p0 = A0, .p1 = A1};
    const App::Segment segmentB{.p0 = B0, .p1 = B1};

    const App::Segments segments{.a = segmentA, .b = segmentB};

    App::RunSample(segments, "The two points are far, don't intersect:\n");
  }

  {
    const rt::Vec3d A0{2.5, 1.0, 1.0};
    const rt::Vec3d A1{-1.1, 1.0, -0.85};
    const rt::Vec3d B0{0.0, 1.0, -0.1};
    const rt::Vec3d B1{-1.0, 2.0, 2.0};

    const App::Segment segmentA{.p0 = A0, .p1 = A1};
    const App::Segment segmentB{.p0 = B0, .p1 = B1};

    const App::Segments segments{.a = segmentA, .b = segmentB};

    App::RunSample(segments,
                   "The two points are closer, but don't intersect:\n");
  }

  {
    // This case attempts to break the math. If we use these values for input in
    // desmos graph, one of the shortest distance points falls outside of the
    // line segment. However, our two closest points should always lie on the
    // two bounded segments.

    // Note: There is a slight discrepancy between the results here and in
    // desmos. A difference of 0.02 and 0.1, which for double precision, might
    // actually be a lot. However, for the current purposes, i am satisfied with
    // the results.
    const rt::Vec3d A0{2.5, 1.0, 1.0};
    const rt::Vec3d A1{-1.1, 1.0, -0.85};
    const rt::Vec3d B0{0.0, 1.0, 1.36};
    const rt::Vec3d B1{-1.0, 2.0, 1.87};

    const App::Segment segmentA{.p0 = A0, .p1 = A1};
    const App::Segment segmentB{.p0 = B0, .p1 = B1};

    const App::Segments segments{.a = segmentA, .b = segmentB};

    App::RunSample(
        segments, "True closest - out of segments. These should be clamped:\n");
  }

  {
    // This is the only case where the two points should intersect. I moved the
    // two lines in desmos so close, that the two points were quite close, but
    // not exactly the same. It was not easy to make them intersect at the
    // current treshold. We are working with two inifinitely thin lines here.
    const rt::Vec3d A0{2.5, 1.0, 1.0};
    const rt::Vec3d A1{-1.1, 1.0, -0.85};
    const rt::Vec3d B0{0.0, 1.0, -0.25};
    const rt::Vec3d B1{-1.0, 2.0, 2.0};

    const App::Segment segmentA{.p0 = A0, .p1 = A1};
    const App::Segment segmentB{.p0 = B0, .p1 = B1};

    const App::Segments segments{.a = segmentA, .b = segmentB};

    App::RunSample(segments,
                   "The only case where the two segments intersect:\n");
  }

  return 0;
}
