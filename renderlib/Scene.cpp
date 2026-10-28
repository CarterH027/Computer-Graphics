#include "Scene.h"

void Scene::addShape(std::shared_ptr<Shape> shape) {
    shapes.push_back(shape);
}


void Scene::addLight(std::shared_ptr<Light> light){
    lights.push_back(light);
}

void Scene::addCamera(std::shared_ptr<Camera> camera) {
    this->cam = camera;
}

color Scene::computeRayColor(const ray& r, float tmin, float tmax, int depth) const {
    if (depth <= 0) return color(0,0.09,0);
    HitRecord closestHit;
    closestHit.t = tmax;
    bool hitAnything = false;

    for (const auto &shape: shapes) {
        HitRecord tempHit;
        if (shape->intersect(r, tmin, tmax, tempHit)) {
            if (tempHit.t < closestHit.t) {
                closestHit = tempHit;
                hitAnything = true;
                tmax = tempHit.t;
            }
        }
    }

    std::vector<std::shared_ptr<Light>> visible_lights;

    if (hitAnything) {
        for (const auto& light : lights) {
            vec3 lightDir = light->direction(closestHit.point); 
            
            if(dot(closestHit.normal, lightDir) > 0.0f) {
                vec3 shadowOrigin = closestHit.point + (closestHit.normal * 0.001f);
                ray shadowRay = ray(shadowOrigin, lightDir);
                
                if(!isShadowed(shadowRay, light->distance(closestHit.point))){
                    visible_lights.push_back(light);
                } 
            }
        }
        color finalColor = closestHit.shader->rayColor(closestHit, visible_lights, *this, depth);
        return finalColor;
    }    

    if (solidbg) {
        return bgColor;
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * bgGradient1 + a * bgGradient2;
    }

}

bool Scene::isShadowed(const ray& r, float tmax) const {
    float tmin = 0.001f; 
    
    for (const auto& shape : shapes){
        HitRecord tempHit;
        
       
        float local_tmax = tmax; 
        
        if (shape->intersect(r, tmin, local_tmax, tempHit)) {
            
            return true; 
        }
    }
    return false; 
}


