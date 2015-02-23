#include <chrono>
#include <iostream>
#include <future>
#include <vector>
#include <cmath>

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include "classes/image_data.h"
#include "classes/scene.h"
#include "helperfunctions.h"

int main(int argc, char** argv)
{
    using namespace sandtrace;
    namespace chrono = std::chrono;
    namespace opt = boost::program_options;

    opt::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("size,s", opt::value<int>(), "image width and height")
        ("out,o", opt::value<std::string>()->default_value("scene.jpg"))
        ("threads,t", opt::value<int>()->default_value(4));

    opt::variables_map m;
    opt::store(opt::parse_command_line(argc, argv, desc), m);
    opt::notify(m);

    if (m.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    int render_width, render_height;
    if (m.count("size"))
    {
        render_width = render_height = m["size"].as<int>();
    }
    else
    {
        std::cout << "Error: Size was not set" << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }

    std::cout << "Constructing scene...";
    auto sphere_scene = build_sphere_scene();
    std::cout << "done." << std::endl;

    std::cout << "Rendering..." << std::flush;
    auto begin_time = chrono::steady_clock::now();

    auto im_data = image_data{render_width, render_height};

    //Divide the columns of the image among various threads, and render in parallel.
    int number_of_threads = m["threads"].as<int>();
    auto futures = std::vector<std::future<void>>{};
    auto render_task =
    [&](int start_col, int last_col)
    {
        for (int i = start_col; i < last_col; i++)
        {
            for (int j = 0; j < render_height; j++)
            {
                auto pixel_ray = build_ray(sphere_scene.cam, i, j, render_width, render_height);
                im_data(i, j) = ray_traced_color(pixel_ray, sphere_scene);
            }
        }
    };
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
    }

    for (auto& f : futures)
    {
        f.get();
    }

    auto duration = chrono::steady_clock::now() - begin_time;
    std::cout << "done." << std::endl;

    auto hours = chrono::duration_cast<chrono::hours>(duration);
    auto minutes = chrono::duration_cast<chrono::minutes>(duration % chrono::hours(1));
    auto seconds = chrono::duration_cast<chrono::seconds>(duration % chrono::minutes(1));
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration % chrono::seconds(1));
    std::cout << "Rendering time: ";
    std::cout << hours.count() << ":" << minutes.count() << ":" << seconds.count()
        << ":" << milliseconds.count() << std::endl;

    std::string filename = m["out"].as<std::string>();
    std::cout << "Saving to " + filename + "..."<< std::flush;
    save_scene(im_data, "scene.jpg");
    std::cout << "done." << std::endl;

    return 0;
}
