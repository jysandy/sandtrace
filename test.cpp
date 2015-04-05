#define BOOST_TEST_MODULE sandtrace_test
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <glm/glm.hpp>

#include "classes/sphere.hpp"
#include "classes/plane.hpp"
#include "classes/triangle.hpp"
#include "classes/monochrome_texture.hpp"
#include "classes/ray.hpp"

#include <random>
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

const float tolerance = 0.0008f;

using namespace sandtrace;

/***************************************
 * STATIC INPUT TESTING
 ***************************************/

void check_equal_vectors(glm::vec3 l, glm::vec3 r)
{
    for (int i = 0; i < 3; i++)
    {
        BOOST_CHECK_LE(std::abs(l[i] - r[i]), tolerance);
    }
}

triangle dummy_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
    auto ab = b - a;
    auto ac = c - a;
    auto normal = glm::normalize(glm::cross(ab, ac));
    auto uv = glm::vec2();

    auto mat = std::make_shared<material>(glm::vec4(), glm::vec4(), glm::vec4(), 0, 0);
    auto tex = std::make_shared<monochrome_texture>(glm::vec4(1.0, 0.0, 0.0, 1.0));

    return triangle{
        {a, normal, uv}, {b, normal, uv}, {c, normal, uv},
        tex, mat
    };
}

auto triangle1 = dummy_triangle(
    {1, 1, 0}, {8, 3, 0}, {2, 6, 0}
);

auto triangle2 = dummy_triangle(
    {5, 6, 0}, {6, 8, 0}, {13, 3, 0}
);

auto origin = glm::vec3{3, 3, 10};

BOOST_AUTO_TEST_CASE(triangle_miss)
{
    glm::vec3 dummy;

    //Triangle 1

    auto d = glm::vec3{5, 5, 0};
    BOOST_CHECK_EQUAL(triangle1.try_intersects(ray(origin, d - origin), dummy), false);
    d = glm::vec3{2, 1, 0};
    BOOST_CHECK_EQUAL(triangle1.try_intersects(ray(origin, d - origin), dummy), false);

    //Triangle 2

    d = glm::vec3{9, 6, 0};
    BOOST_CHECK_EQUAL(triangle2.try_intersects(ray(origin, d - origin), dummy), false);
    d = glm::vec3{7.5, 5, 0};
    BOOST_CHECK_EQUAL(triangle2.try_intersects(ray(origin, d - origin), dummy), false);
}

BOOST_AUTO_TEST_CASE(triangle_hit)
{
    glm::vec3 intersection;

    //Triangle 1

    auto expected_intersection = glm::vec3{5, 3, 0};
    BOOST_CHECK_EQUAL(triangle1.try_intersects(ray(origin, expected_intersection - origin), intersection), true);
    check_equal_vectors(expected_intersection, intersection);
    expected_intersection = glm::vec3{2, 5, 0};
    BOOST_CHECK_EQUAL(triangle1.try_intersects(ray(origin, expected_intersection - origin), intersection), true);
    check_equal_vectors(expected_intersection, intersection);
    expected_intersection = glm::vec3{8, 3, 0};
    BOOST_CHECK_EQUAL(triangle1.try_intersects(ray(origin, expected_intersection - origin), intersection), true);
    check_equal_vectors(expected_intersection, intersection);

    //Triangle 2

    expected_intersection = glm::vec3{8, 6, 0};
    BOOST_CHECK_EQUAL(triangle2.try_intersects(ray(origin, expected_intersection - origin), intersection), true);
    check_equal_vectors(expected_intersection, intersection);
    expected_intersection = glm::vec3{11, 4, 0};
    BOOST_CHECK_EQUAL(triangle2.try_intersects(ray(origin, expected_intersection - origin), intersection), true);
    check_equal_vectors(expected_intersection, intersection);
    expected_intersection = glm::vec3{5, 6, 0};
    BOOST_CHECK_EQUAL(triangle2.try_intersects(ray(origin, expected_intersection - origin), intersection), true);
    check_equal_vectors(expected_intersection, intersection);
}

/****************************************
 * RANDOMIZED TESTING
 ****************************************/

std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<float> zero_one_distribution{0.0f, 1.0f};
std::uniform_real_distribution<float> float_distribution{-100.0f, 100.0f};

auto rand_norm_float = std::bind(zero_one_distribution, generator);
auto rand_float = std::bind(float_distribution, generator);


//Generates a random point inside the given triangle
glm::vec3 point_inside(const triangle& t)
{

    auto a = rand_norm_float();
    auto b = rand_norm_float();
    auto c = 1.0f - b - a;

    BOOST_REQUIRE_LE(1.0f - (a + b + c), tolerance);
    BOOST_REQUIRE_GE(1.0f - (a + b + c), 0);

    return
        a * t.vertices_[0].position
        + b * t.vertices_[1].position
        + c * t.vertices_[2].position;
}

//Generates a random point outside the triangle in the same plane.
glm::vec3 point_outside(const triangle& t)
{
    auto a = rand_float();
    auto b = rand_float();
    auto c = rand_float();

    BOOST_REQUIRE_NE(a + b + c, 1.0f);

    return
        a * t.vertices_[0].position
        + b * t.vertices_[1].position
        + c * t.vertices_[2].position;
}

//Generates a random vector3.
glm::vec3 random_vector()
{
    float a = rand_float();
    float b = rand_float();
    float c = rand_float();

    auto x = glm::vec3(a, b, c);
    return x;
}

//Generates a random point outside the plane of the given triangle.
glm::vec3 point_outside_plane(const triangle& t)
{
    auto p = random_vector();
    auto a = t.vertices_[0].position;

    if (std::abs(glm::dot(p - a, t.vertices_[0].normal)) < tolerance)
    {
        p += 4.0f * t.vertices_[0].normal;
    }

    return p;
}

//Generates a random triangle with dummy texcoords, texture and material
triangle random_triangle()
{
    auto a = random_vector();
    auto b = random_vector();
    auto c = random_vector();

    auto ab = b - a;
    auto ac = c - a;
    auto normal = glm::normalize(glm::cross(ab, ac));
    auto uv = glm::vec2();

    auto mat = std::make_shared<material>(glm::vec4(), glm::vec4(), glm::vec4(), 0, 0);
    auto tex = std::make_shared<monochrome_texture>(glm::vec4(1.0, 0.0, 0.0, 1.0));

    return triangle{
        {a, normal, uv}, {b, normal, uv}, {c, normal, uv},
        tex, mat
    };
}


BOOST_AUTO_TEST_CASE(random_triangle_miss)
{
    //These test cases are all supposed to miss the triangles.
    std::vector<triangle> triangles;
    for (int i = 0; i < 5; i++)
    {
        triangles.emplace_back(random_triangle());
    }

    for (auto t : triangles)
    {
        auto origin = point_outside_plane(t);
        auto direction = point_outside(t) - origin;
        auto miss_ray = ray{origin, direction};
        glm::vec3 dummy;
        BOOST_CHECK_EQUAL(t.try_intersects(miss_ray, dummy), false);
    }
}

BOOST_AUTO_TEST_CASE(random_triangle_hit)
{
    //These test cases are all supposed to hit the triangles.
    std::vector<triangle> triangles;

    for (int i = 0; i < 5; i++)
    {
        triangles.emplace_back(random_triangle());
    }

    for (auto& t : triangles)
    {
        auto origin = point_outside_plane(t);
        auto expected_intersection = point_inside(t);
        auto direction = expected_intersection - origin;
        auto hit_ray = ray{origin, direction};
        glm::vec3 intersection(0);
        auto hit = t.try_intersects(hit_ray, intersection);
        BOOST_CHECK_EQUAL(hit, true);
        check_equal_vectors(expected_intersection, intersection);
    }
}
