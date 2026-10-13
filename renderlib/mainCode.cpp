#include "vec3.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "hittable.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Shape.h"
#include "Scene.h"
#include "Shader.h"
#include "Lambertian.h"
#include "BlinnPhong.h"
#include "Light.h"
#include "PointLight.h"
#include "Functions.h"
#include "Mirror.h"

#include <memory>
#include <limits>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {

    int fb_height = 500;
    int fb_width = 500;
    point3 cam_origin = point3(0.0, 2.0, 0.0);
    vec3 cam_viewdir = vec3(0.0, -0.3, -1.0);
    double camera_focalLength = 1.0;
    double imagePlane_width = 1;
    double imagePlane_height = 1;
    Framebuffer fb = Framebuffer(fb_height, fb_width);
    std::shared_ptr<Camera> cam = std::make_shared<PerspectiveCamera>(cam_origin, cam_viewdir, camera_focalLength, imagePlane_width, imagePlane_height, fb_width, fb_height);

    int depth = 4;
    //Colors for sky background gradient
    color bg1 = color(1.0,1.0,1.0);
    color bg2 = color(0.5,0.7,1.0);

    //textures
    auto lambertian = std::make_shared<Lambertian>();
    auto glossy = std::make_shared<BlinnPhong>(200);
    auto satin = std::make_shared<BlinnPhong>(16);
    auto mirror = std::make_shared<Mirror>();


    Scene scene = Scene(bg1, bg2);
    //floor sphere?
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(0, -100.5, -1.0), 100, color(0.25, 0.25, 0.25), lambertian
        )
    );

    color sphereColor = color(0.1,0.67,.15);
    //shape definitions
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(0, 0, -7), 0.5, sphereColor, satin
        )
    );
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(-1.5, 0, -7), 0.5, sphereColor, lambertian
        )
    );
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(1.5, 0, -7), 0.5, sphereColor, glossy
        )
    );
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(0, 2, -8), 1, sphereColor, mirror
        )
    );
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(0, 1, 4), 4, sphereColor, mirror
        )
    );
    
    //lights 
    scene.addLight(
        std::make_shared<PointLight>(vec3(-6.0, 2.0, -1), color(0.4,0.05,.3))
    );
    scene.addLight(
        std::make_shared<PointLight>(vec3(6.0, 4.0, -1), color(0.1,0.85, 0.7))
    );

    //end of variables to play with

    float inf = std::numeric_limits<float>::max();
    int rpp_Nsquare = 4;
    
    for (int x = 0; x < fb_width; ++x){
        for(int y = 0; y < fb_height; ++y){
            color c = color(0.0,0.0,0.0);
            for(int i = 0; i<rpp_Nsquare; ++i){
                for (int j = 0; j<rpp_Nsquare; ++j){
                    ray r;

                    float iOffset = (i + randomOffset())/rpp_Nsquare;
                    float jOffset = (j + randomOffset())/rpp_Nsquare;

                    cam->generateRay(x + iOffset, y + jOffset, r);
                    c += scene.computeRayColor(r, 1.0, inf, depth);
                }
            }

            c = c / (rpp_Nsquare*rpp_Nsquare);

            fb.setPixelColor(x, y ,c);
        }
    }

    fb.exportToPNG("ProjPic_1.png");

    return 0;
}