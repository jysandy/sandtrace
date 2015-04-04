#include <chrono>
#include <iostream>
#include <cmath>

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include "classes/image_data.hpp"
#include "classes/scene.hpp"
#include "helperfunctions.hpp"

int main(int argc, char** argv)
{
    using namespace sandtrace;
    namespace chrono = std::chrono;
    namespace opt = boost::program_options;

    opt::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("size,s", opt::value<int>(), "image width and height")
        ("out,o", opt::value<std::string>()->default_value("scene.jpg"), "output file")
        ("threads,t", opt::value<int>()->default_value(4), "number of threads")
        ("fbx", opt::value<std::string>(), "FBX input file")
        ("tex", opt::value<std::string>(), "Texture input file");

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

    std::string fbx_filename, tex_filename;
    if (m.count("fbx") && m.count("tex"))
    {
        fbx_filename = m["fbx"].as<std::string>();
        tex_filename = m["tex"].as<std::string>();
    }
    else
    {
        std::cout << desc << std::endl;
        return 1;
    }

    std::cout << "Constructing scene..." << std::flush;
    auto render_scene = scene::from_fbx_file(fbx_filename, tex_filename);
    std::cout << "done." << std::endl;

    int number_of_threads = m["threads"].as<int>();
    std::cout << "Rendering..." << std::flush;
    auto begin_time = chrono::steady_clock::now();
    //Render!!
    auto im_data = render_image(render_width, render_height, render_scene, number_of_threads);
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
