#include "myheader.h"
#include <iostream>
#include <cstdlib>  // for atoi and atof
#include <vector>
#include "scene.hpp"

#include <opencv2/opencv.hpp>

#include <opencv2/opencv.hpp>
#include <vector>

int show(const Scene& scene) {
    // Dimensions of the image
    int height = 100;
    int width = 100;

    // Example 3D vector (height, width, colors)
    std::vector<std::vector<std::vector<int>>> pixels(height, std::vector<std::vector<int>>(width, std::vector<int>(3, 0)));

    // Ray trace from camera points to scene objects
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << "i="<<i<<", j="<<j<< std::endl;
            // Convert (i,j) to x,y,z point around camera
            Vector3D rayOrigin = scene.cam()->getRayOrigin(height, width, i, j);
            std::cout << "rayOrigin calcd " << rayOrigin.toString() << std::endl;
            // Check if each object intersects with ray.
            for(auto& obj : scene.objects()) {
                std::cout << "prehit" << std::endl;
                std::optional<HitInfo> hit = obj->intersect(rayOrigin, scene.cam()->orientation());
                std::cout << "posthit" << std::endl;
                // If intersects, check if bounce angle hits the light.
                // TODO: Refactor to work with n-bounces
                // TODO: Calc color correctly
                if (hit.has_value()) {
                    std::cout << "hit" << std::endl;
                    for (const std::unique_ptr<Light>& light : scene.lights()) {
                        std::optional<HitInfo> lightHit = light->intersect(*hit.value().hitPoint, *hit.value().bounceDir);
                        if (lightHit.has_value()) {
                            std::cout << "lighthit" << std::endl;
                            pixels[i][j][0] = 125;
                            pixels[i][j][1] = 255;
                            pixels[i][j][2] = 0;
                        }
                    }
                }
            }
        }
    }

    // Create a Mat object with 3 channels
    cv::Mat image(height, width, CV_8UC3);

    // Copy the data from the 3D vector to the Mat object
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            image.at<cv::Vec3b>(i, j) = cv::Vec3b(pixels[i][j][0], pixels[i][j][1], pixels[i][j][2]);
        }
    }

    // Display the image
    cv::imshow("Image", image);
    cv::waitKey(0);

    return 0;
}


int main(int argc, char *argv[]) {
    Scene scene = Scene();
    std::unique_ptr<SceneObject> obj = std::make_unique<SphereSceneObject>(0.1, 1, 0, 1, 1, 1, 1, 2);
    scene.addObject(std::move(obj));
    auto cam = std::make_unique<Camera>(-4, 1, 0, 0, 0.2, 0.1, 4);
    scene.setCamera(std::move(cam));
    auto light = std::make_unique<Light>(0, 15, 0, 1, 1, 1, 23);
    scene.addLight(std::move(light));

    show(scene);

    // if(argc != 4) {  // We expect 3 arguments (besides the program name)
    //     std::cerr << "Usage: " << argv[0] << " <integer> <float> <string>\n";
    //     return 1;
    // }

    // int myInt = std::atoi(argv[1]);
    // float myFloat = std::atof(argv[2]);
    // std::string myString = argv[3];

    // std::cout << "Integer: " << myInt << "\n";
    // std::cout << "Float: " << myFloat << "\n";
    // std::cout << "String: " << myString << "\n";

    return 0;
}
