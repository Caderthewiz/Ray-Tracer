# CMakeList.txt : CMake project for Simple Ray Tracer, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CMakeTarget "Simple Ray Tracer.cpp"  "vec3.h" "color.h" "ray.h" "hittable.h" "sphere.h" "hittable_list.h" "math_util.h" "interval.h"  "camera.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
