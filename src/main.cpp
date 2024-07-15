#include <chrono>
#include <iostream>
#include <cmath>

#include "image_data.hpp"
#include "scene/scene.hpp"
#include "renderer.hpp"

int main(int argc, char** argv)
{
    using namespace sandtrace;
    namespace chrono = std::chrono;

    int render_width, render_height;
    render_width = render_height = 1500;

    std::cout << "Constructing scene..." << std::flush;
    auto sphere_scene = build_sphere_scene();
    std::cout << "done." << std::endl;

    //int number_of_threads = m["threads"].as<int>();
    int number_of_threads = 4;
    std::cout << "Rendering..." << std::flush;
    auto begin_time = chrono::steady_clock::now();
    //Render!!
    auto im_data = render_image(render_width, render_height, sphere_scene, number_of_threads);
    auto duration = chrono::steady_clock::now() - begin_time;
    std::cout << "done." << std::endl;

    auto hours = chrono::duration_cast<chrono::hours>(duration);
    auto minutes = chrono::duration_cast<chrono::minutes>(duration % chrono::hours(1));
    auto seconds = chrono::duration_cast<chrono::seconds>(duration % chrono::minutes(1));
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration % chrono::seconds(1));
    std::cout << "Rendering time: ";
    std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count()
        << ":" << milliseconds.count() << std::endl;

    std::string filename = "scene.png";
    std::cout << "Saving to " + filename + "..."<< std::flush;
    save_scene(im_data, filename);
    std::cout << "done." << std::endl;

    return 0;
}
