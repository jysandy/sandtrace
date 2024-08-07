#ifndef __SANDTRACE_HELPERFUNCTIONS_H__
#define __SANDTRACE_HELPERFUNCTIONS_H__

#include <memory>
#include <string>
#include <vector>
#include <stack>
#include <future>
#include <limits>
#include <algorithm>
#include <iostream>
#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <boost/gil.hpp>

#include "scene/scene.hpp"
#include "geometry/sphere.hpp"
#include "geometry/plane.hpp"
#include "image_data.hpp"
#include "scene/camera.hpp"
#include "geometry/primitive.hpp"
#include "lighting/material.hpp"
#include "geometry/polygon_vertex.hpp"


namespace sandtrace
{
    /*
     * Renders the image into an image_data.
     */
    image_data render_image(int render_width, int render_height, scene target_scene, int number_of_threads);

    /*
     * Generates a ray from the camera to the pixel at (i, j) in the image plane.
     */
     ray build_ray(const camera& cam, int i, int j, int render_width, int render_height);
    /*
     * Used for thresholding in adaptive depth control.
     */
    bool operator<=(const glm::vec4& left, const glm::vec4& right);

    /*
     * Returns a traced ray's color.
     */
    glm::vec4 ray_traced_color(const ray& pixel_ray, const scene& target_scene);

    /*
     * Returned by nearest_intersection (see below)
     */
    class intersection_data
    {
        bool intersects_;
        material mat_;
        color_vertex vertex_;

    public:
        intersection_data() : intersects_(false),
        mat_(
            glm::vec4(), glm::vec4(), glm::vec4(), 0.0f, 0.0f
        )
        {}

        intersection_data(bool i, material m, color_vertex ver)
        : intersects_(i), mat_(m), vertex_(ver)
        {
        }

        const bool& intersects() const {return intersects_; }
        const material& mat() const { return mat_; }
        const glm::vec3& intersection_point() const { return vertex_.position; }
        const glm::vec3& normal() const { return vertex_.normal; }
        const glm::vec4& color() const { return vertex_.color; }

    };

    /*
     * Returns data of the closest primitive which intersects the given ray.
     */
    intersection_data nearest_intersection(const ray& r, const scene& s);

    /*
     * Applies the Phong model to compute the color at the intersection point.
     */
    glm::vec4 phong_color(const ray& eye_to_point, const intersection_data& intersection, const scene& target_scene);

    /*
     * Computes the contribution of directional lights in the scene to the final color.
     */
    glm::vec4 directional_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene);

    /*
     * Computes the contribution of point lights in the scene to the final color.
     */
    glm::vec4 point_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene);

    /*
     * Computes the contribution of spot lights in the scene to the final color.
     */
    glm::vec4 spot_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene);

    /*
     * Tests if the ray intersects ANY primitive.
     */
    bool is_blocked(const ray& r, const scene& s);

    /*
     * Tests if the ray is blocked at any point between its origin and the limit.
     */
    bool is_blocked(const ray& r, const scene& s, const glm::vec3& limit);

    /*
     * Save the scene as a PNG image.
     */
    void save_scene(image_data img_data, std::string filename);
}

#endif
