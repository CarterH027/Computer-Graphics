#include "vec3.h"
#include "Framebuffer.h"
#include "ray.h"
#include "Scene.h"
#include "Functions.h"
#include "SceneLoader.h"
#include "SceneParser_JSON.h"

#include <memory>
#include <limits>
#include <vector>
#include <iostream>
#include <omp.h>

int main(int argc, char** argv) {

    int fb_height = 500;
    int fb_width = 500;
    Framebuffer fb = Framebuffer(fb_height, fb_width);
    int depth = 5;
    float inf = std::numeric_limits<float>::max();
    int rpp_Nsquare = 4;


    Scene scene;

    std::shared_ptr<ISceneLoader> loader = std::make_shared<SceneLoader>(scene);
    SceneParser_JSON parser(loader);

    std::string filename = argv[1];
    parser.parseFileData(filename);
    
    std::shared_ptr<Camera> cam = scene.cam;

//#pragma omp parallel for
    for (int x = 0; x < fb_width; ++x){
        for(int y = 0; y < fb_height; ++y){
            color c = color(0.0,0.0,0.0);
            for(int i = 0; i<rpp_Nsquare; ++i){
                for (int j = 0; j<rpp_Nsquare; ++j){
                    ray r;

                    float iOffset = (i + randomOffset())/rpp_Nsquare;
                    float jOffset = (j + randomOffset())/rpp_Nsquare;

                    cam->generateRay(x + iOffset, y + jOffset, r, fb_height, fb_width);
                    c += scene.computeRayColor(r, 1.0, inf, depth);
                }
            }

            c = c / (rpp_Nsquare*rpp_Nsquare);

            fb.setPixelColor(x, y ,c);
            
        }
    }

    fb.exportToPNG("Json_Test.png");

    return 0;
}