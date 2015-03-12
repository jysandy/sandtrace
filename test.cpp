#define BOOST_TEST_MODULE sandtrace_test
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <glm/glm.hpp>

#include "classes/sphere.hpp"
#include "classes/plane.hpp"

const float tolerance = 0.0008f;

BOOST_AUTO_TEST_CASE(sphere_intersection)
{
    auto dummy_sphere = sandtrace::sphere(glm::vec3(0, 0, 0), 2.0f, sandtrace::material());

    glm::vec3 intersection_point;

    //This ray is outside the sphere and doesn't intersect at all.
    auto outside_ray = sandtrace::ray(glm::vec3(3, 0, 0), glm::vec3(3, 0, 0) - dummy_sphere.position);
    BOOST_CHECK(!dummy_sphere.try_intersects(outside_ray, intersection_point));

    //This ray is a tangent to the sphere and so should not intersect.
    auto tangent_ray = sandtrace::ray(glm::vec3(2, 0, 0), glm::vec3(0, 0, 1));
    BOOST_CHECK(!dummy_sphere.try_intersects(tangent_ray, intersection_point));
}
