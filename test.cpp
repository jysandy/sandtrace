#define BOOST_TEST_MODULE sandtrace_test
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <glm/glm.hpp>

#include "classes/sphere.hpp"
#include "classes/plane.hpp"

const float tolerance = 0.0008f;

/*
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

    //This ray originates inside the ray and so should intersect.
    auto inside_ray = sandtrace::ray(glm::vec3(0, 1, -1), glm::vec3(0, 1, -1));
    BOOST_CHECK(dummy_sphere.try_intersects(inside_ray, intersection_point));

    //This ray originates outside and passes straight through.
    auto pos = glm::vec3(3, 4, 2);
    auto direction = glm::vec3(0, 1, 0) - pos;
    auto through_ray = sandtrace::ray(pos, direction);
    BOOST_CHECK(dummy_sphere.try_intersects(through_ray, intersection_point));
}

BOOST_AUTO_TEST_CASE(plane_intersection)
{
    auto dummy_plane = sandtrace::plane(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), sandtrace::material());
    glm::vec3 intersection_point;

    //This ray doesn't intersect.
    auto away_ray = sandtrace::ray(glm::vec3(2, 1, 1), glm::vec3(1, 3, 4));
    BOOST_CHECK(!dummy_plane.try_intersects(away_ray, intersection_point));

    //This ray intersects.
    auto hit_ray = sandtrace::ray(glm::vec3(2, 1, 1), glm::vec3(4, -3, 2));
    BOOST_CHECK(dummy_plane.try_intersects(hit_ray, intersection_point));
}
*/
