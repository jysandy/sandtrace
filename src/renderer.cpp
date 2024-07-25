#include "renderer.hpp"
#include <iostream>
#include <cmath>
#include <boost/gil/io/write_view.hpp>
#include "textures/monochrome_texture.hpp"
#include "lighting/colour.hpp"

namespace sandtrace
{
    //The distance moved towards the light source when computing the shadow ray.
    const static float epsilon = 0.0008f;

    //For debugging.
    std::ostream& operator<<(std::ostream& out, const glm::vec3& vec)
    {
        out << "[" << vec[0] << ", "
            << vec[1] << ", "
            << vec[2] << "]";
        return out;
    }

    scene build_sphere_scene()
    {
        auto primitives = scene::primitive_vector{};

        //Add the sphere
        auto sphere_position = glm::vec3{ 10, 10, -10 };
        auto sphere_radius = 5.0f;

        auto sphere_colour = glm::vec4(0.8, 0.8, 0.8, 1);
        auto sphere_mat = material
        {
            sphere_colour,
            sphere_colour,
            glm::vec4{0.3, 0.3, 0.3, 1.0},
            256,
            0.7
        };
        primitives.push_back(std::make_shared<sphere>(sphere_position, 
                                                      sphere_radius, 
                                                      sphere_mat,
                                                      std::make_shared<monochrome_texture>(sphere_colour)));

        auto sphere2_colour = glm::vec4{ 1, 0, 0, 1.0 };

        auto sphere2_mat = material
        {
            sphere2_colour,
            sphere2_colour,
            glm::vec4{0.8, 0.8, 0.8, 1.0},
            200,
            0.05
        };

        auto sphere2_position = sphere_position + glm::vec3{ 25, 0, 0 };
        sphere2_position.y = 7;
        auto sphere2_radius = 7.0f;
        primitives.push_back(std::make_shared<sphere>(sphere2_position, 
                                                      sphere2_radius, 
                                                      sphere2_mat,
                                                      std::make_shared<monochrome_texture>(sphere2_colour)));

        //Add the plane
        auto plane_point = glm::vec3{ 5, 0, -5 };
        auto plane_normal = glm::vec3{ 0, 1, 0 };
        auto plane_colour = glm::vec4
        {
            0xDA / 255.0f,
            0xDA / 255.0f,
            0xDA / 255.0f,
            1
        };//A silvery-grey colour
        auto plane_mat = material
        {
            plane_colour,
            plane_colour,
            glm::vec4{0.5, 0.5, 0.5, 1.0},
            128,
            0.1
        };

        auto plane2_mat = material
        {
            glm::vec4(0.5, 0.3, 0.3, 1),
            glm::vec4(0.5, 0.3, 0.3, 1),
            glm::vec4{0.5, 0.5, 0.5, 1.0},
            128,
            0
        };
        primitives.push_back(std::make_shared<plane>(plane_point, 
                                                     plane_normal, 
                                                     plane_mat,
                                                     std::make_shared<monochrome_texture>(plane_colour)));


        primitives.push_back(std::make_shared<plane>(glm::vec3{ 5, 0, -30 },
                                                     glm::vec3{ 0, 0, 1 },
                                                     plane2_mat,
                                                     std::make_shared<monochrome_texture>(plane_colour)));

        auto the_scene = scene::from_json("scenes/scene2.json");
        the_scene.primitives = primitives;
        return the_scene;
    }

    image_data render_image(int render_width, int render_height, scene target_scene, int number_of_threads)
    {
        auto im_data = image_data{render_width, render_height};
        auto render_task =
        [&](int start_col, int last_col)
        {
            for (int i = start_col; i < last_col; i++)
            {
                for (int j = 0; j < render_height; j++)
                {
                    auto pixel_ray = build_ray(target_scene.cam, i, j, render_width, render_height);
                    im_data(i, j) = ray_traced_color(pixel_ray, target_scene);
                }
            }
        };
        auto futures = std::vector<std::future<void>>{};
        int cols_per_thread = std::ceil(static_cast<float>(render_width) / number_of_threads);
        //For each thread
        for (int i = 0; i < number_of_threads; i++)
        {
            int start_col = i * cols_per_thread;
            int end_col = start_col + cols_per_thread;
            if (end_col + number_of_threads >= render_width)
            {
                //If this thread is the last, then set the end row to the last row.
                end_col = render_width;
            }
            futures.push_back(std::async(std::launch::async, [=](){ render_task(start_col, end_col); }));
            // futures.push_back(std::async([=](){ render_task(start_col, end_col); }));
        }

        for (auto& f : futures)
        {
            f.get();
        }

        return im_data;
    }

    ray build_ray(const camera& cam, int i, int j, int render_width, int render_height)
    {
        auto alpha = std::tan(cam.fov / 2.0f) * ((i - (render_width / 2.0f)) / (render_width / 2.0f) );
        auto beta = std::tan(cam.fov / 2.0f) * (((render_height / 2.0f) - j) / (render_height / 2.0f) );

        //Form a left-handed orthonormal basis. Camera looks down the +w direction.
        auto w = glm::normalize(cam.look_at - cam.look_from);
        auto u = glm::normalize(glm::cross(w, cam.up));
        auto v = glm::normalize(glm::cross(u, w));

        // std::cout << w << std::endl;

        return ray{cam.look_from, alpha * u + beta * v + w};
    }

    bool operator<=(const glm::vec4& left, const glm::vec4& right)
    {
        return left.x <= right.x &&
               left.y <= right.y &&
               left.z <= right.z &&
               left.w <= right.w;
    }

    glm::vec4 ray_traced_color(const ray& pixel_ray, const scene& target_scene)
    {
        const glm::vec4 empty_color{0.0, 0.0, 0.0, 1.0};
        const int max_stack_depth = 50;

        //The recursive ray-tracing is performed iteratively, using a stack.
        struct stack_entry
        {
            glm::vec4 color;
            float reflectance;

            stack_entry(glm::vec4 c, float r) : color(c), reflectance(r) {}
        };
        std::stack<stack_entry> recursion_stack;
        auto current_ray = pixel_ray;
        //This prevents the stack from ending up empty,
        //if the ray intersected no primitive.
        recursion_stack.emplace(empty_color, 1.0f);

        while (recursion_stack.size() < max_stack_depth + 1)
        {
            auto data = nearest_intersection(current_ray, target_scene.primitives);
            if (!data.intersects())
            {
                //If the ray did not intersect any primitive
                recursion_stack.emplace(empty_color, 1.0f);
                break;
            }

            auto color = phong_color(current_ray, data, target_scene);
            recursion_stack.emplace(color, data.mat().reflectance);

            if (color <= glm::vec4{0.001, 0.001, 0.001, 1.0})
            {
                break;
            }

            auto new_direction = glm::reflect(current_ray.direction, data.normal());
            current_ray = ray{data.intersection_point(), new_direction};
        }

        glm::vec4 final_color = recursion_stack.top().color;
        recursion_stack.pop();

        while (!recursion_stack.empty())
        {
            auto entry = recursion_stack.top();
            recursion_stack.pop();
            final_color =saturate(entry.color + entry.reflectance * final_color);
        }

        return final_color;
    }

    intersection_data nearest_intersection(const ray& r, const scene::primitive_vector& primitives)
    {
        auto closest_primitive = primitives[0];
        glm::vec3 closest_intersection;
        auto closest_distance = std::numeric_limits<float>::max();
        bool intersects = false;
        // The ray is moved so that it doesn't intersect with the surface 
        // that it originates from.
        auto moved_r = ray(r.origin + epsilon * r.direction, r.direction);

        for (const auto& p : primitives)
        {
            glm::vec3 intersection;
            if (p->try_intersects(moved_r, intersection))
            {
                intersects = true;
                float distance = glm::length(intersection - moved_r.origin);
                if (distance < closest_distance)
                {
                    closest_distance = distance;
                    closest_intersection = intersection;
                    closest_primitive = p;
                }
            }
        }

        if (!intersects)
        {
            return intersection_data();
        }

        if (closest_distance == std::numeric_limits<float>::max())
        {
            throw std::runtime_error("closest distance not changed");
        }

        return intersection_data(
            true, closest_primitive->mat(), closest_primitive->vertex_at(closest_intersection)
        );
    }

    glm::vec4 phong_color(const ray& eye_to_point, const intersection_data& intersection, const scene& target_scene)
    {
        auto dcolor = directional_phong_color(eye_to_point, intersection, target_scene);
        auto pcolor = point_phong_color(eye_to_point, intersection, target_scene);
        auto scolor = spot_phong_color(eye_to_point, intersection, target_scene);

        auto final_color = dcolor + pcolor + scolor;
        return saturate(final_color);
    }

    glm::vec4 directional_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene)
    {
        auto final_color = glm::vec4{0, 0, 0, 1};

        for (const auto& dlight : target_scene.directional_lights)
        {
            final_color += idata.color() * dlight.ambient * idata.mat().ambient;
            final_color = saturate(final_color);

            //For a directional light, the shadow ray is simply the negative
            //of the light's direction.
            auto light_vector = -dlight.direction;
            light_vector = glm::normalize(light_vector);
            auto shadow_ray = ray{idata.intersection_point(), light_vector};
            if (is_blocked(shadow_ray, target_scene.primitives))
            {
                continue;
            }

            //Diffuse component
            auto kd = std::max(glm::dot(light_vector, idata.normal()), 0.0f);
            final_color += idata.color() * kd * dlight.diffuse * idata.mat().diffuse;
            final_color = saturate(final_color);
            //Specular component
            auto reflected_ray = glm::reflect(-light_vector, idata.normal());
            auto ks = std::max(glm::dot(reflected_ray, -eye_to_point.direction), 0.0f);
            ks = glm::pow(ks, idata.mat().shininess);
            final_color += ks * dlight.specular * idata.mat().specular;
            final_color = saturate(final_color);
        }

        return final_color;
    }

    glm::vec4 point_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene)
    {
        auto final_color = glm::vec4{0, 0, 0, 1};

        for (const auto& plight : target_scene.point_lights)
        {
            final_color += idata.color() * plight.ambient * idata.mat().ambient;
            final_color = saturate(final_color);

            //Here the shadow ray is the ray from the point of intersection to the light.
            auto light_vector = plight.position - idata.intersection_point();
            auto d = glm::length(light_vector);
            light_vector = glm::normalize(light_vector);
            auto shadow_ray = ray{idata.intersection_point() + epsilon * light_vector, light_vector};
            if (is_blocked(shadow_ray, target_scene.primitives, plight.position))
            {
                continue;
            }

            auto attenuation_factor = 1.0f / (plight.a0 + plight.a1 * d + plight.a2 * d * d);

            //Diffuse component
            auto kd = std::max(glm::dot(light_vector, idata.normal()), 0.0f);
            final_color += idata.color() * kd * plight.diffuse * idata.mat().diffuse * attenuation_factor;
            final_color = saturate(final_color);

            //Specular component
            auto ref = glm::reflect(-light_vector, idata.normal());
            auto ks = std::max(glm::dot(ref, -eye_to_point.direction), 0.0f);
            ks = glm::pow(ks, idata.mat().shininess);
            final_color += ks * plight.specular * idata.mat().specular * attenuation_factor;
            final_color = saturate(final_color);
        }

        return final_color;
    }

    glm::vec4 spot_phong_color(const ray& eye_to_point, const intersection_data& idata, const scene& target_scene)
    {
        auto final_color = glm::vec4{0, 0, 0, 1};

        for (const auto& slight : target_scene.spot_lights)
        {
            final_color += idata.color() * slight.ambient * idata.mat().ambient;
            final_color = saturate(final_color);

            auto light_vector = slight.position - idata.intersection_point();
            auto d = glm::length(light_vector);
            light_vector = glm::normalize(light_vector);
            auto shadow_ray = ray{idata.intersection_point() + epsilon * light_vector, light_vector};
            if (is_blocked(shadow_ray, target_scene.primitives, slight.position))
            {
                continue;
            }

            auto attenuation_factor = 1.0f / (slight.a0 + slight.a1 * d + slight.a2 * d * d);
            // TODO: This is not right
            // If the dot product is less than 1, then the intensity factor decreases with the exponent
            // Maybe invert it before pow or add a constant instead?
            // Added 1 for now. Evaluate other options?
            auto intensity_factor = glm::pow(
                                    1 + std::max(glm::dot(-light_vector, slight.direction), 0.0f),
                                    slight.power);

            //Diffuse component
            auto kd = std::max(glm::dot(light_vector, idata.normal()), 0.0f);
            final_color += idata.color() * kd * slight.diffuse * idata.mat().diffuse * attenuation_factor * intensity_factor;
            final_color = saturate(final_color);

            //Specular component
            auto ref = glm::reflect(-light_vector, idata.normal());
            auto ks = std::max(glm::dot(ref, -eye_to_point.direction), 0.0f);
            ks = glm::pow(ks, idata.mat().shininess);
            final_color += ks * slight.specular * idata.mat().specular * attenuation_factor * intensity_factor;
            final_color = saturate(final_color);
        }

        return final_color;
    }

    bool is_blocked(const ray& r, const scene::primitive_vector& primitives)
    {
        auto moved_r = ray{r.origin + epsilon * r.direction, r.direction};
        for (auto p : primitives)
        {
            glm::vec3 intersection;
            if (p->try_intersects(moved_r, intersection))
            {
                return true;
            }
        }

        return false;
    }

    bool is_blocked(const ray& r, const scene::primitive_vector& primitives, const glm::vec3& limit)
    {
        auto moved_r = ray{r.origin + epsilon * r.direction, r.direction};
        for (auto p : primitives)
        {
            glm::vec3 intersection;
            if (p->try_intersects(moved_r, intersection))
            {
                auto max_length = glm::length(limit - moved_r.origin);
                auto length = glm::length(intersection - moved_r.origin);
                if (length < max_length)
                {
                    return true;
                }
            }
        }

        return false;
    }

    void save_scene(image_data img_data, std::string filename)
    {
        namespace gil = boost::gil;

        auto target_image = gil::rgb8_image_t{img_data.render_width, img_data.render_height};
        auto target_image_view = gil::view(target_image);

        for (int x = 0; x < target_image_view.width(); x++)
        {
            for (int y = 0; y < target_image_view.height(); y++)
            {
                //Mapping the color values of img_data, which are floats in [0, 1],
                //into integers in [0, 255].
                gil::get_color(target_image_view(x, y), gil::red_t()) = static_cast<int>(img_data(x, y).r * 255);
                gil::get_color(target_image_view(x, y), gil::green_t()) = static_cast<int>(img_data(x, y).g * 255);
                gil::get_color(target_image_view(x, y), gil::blue_t()) = static_cast<int>(img_data(x, y).b * 255);
            }
        }

        gil::write_view(filename, target_image_view, gil::png_tag());
    }
}
