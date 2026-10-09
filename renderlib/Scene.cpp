#include "Scene.h"

void Scene::addShape(std::shared_ptr<Shape> shape) {
    shapes.push_back(shape);
}


void Scene::addLight(std::shared_ptr<Light> light){
    lights.push_back(light);
}


color Scene::computeRayColor(const ray& r, float tmin, float tmax) {
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

    

    if (hitAnything) {
        color finalColor = closestHit.shader->rayColor(closestHit, lights);
        for (const auto& light : lights) {
            if(dot(closestHit.normal, light->direction(closestHit.normal)) > 0.0f) {
               ray shadowRay = ray(closestHit.point, light->direction(closestHit.point));
                if(isShadowed(shadowRay, light->distance(closestHit.point), closestHit.shape)){
                    finalColor *= 0.5;
                } 
            }
            
        }
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

bool Scene::isShadowed(const ray& r, float tmax, const Shape* currentShape) {
    HitRecord closestHit;
    closestHit.t = tmax;
    float tmin = 0.001;
    bool hitAnything = false;
    

    for (const auto& shape : shapes){
        HitRecord tempHit;
        if(shape->intersect(r, tmin, tmax, tempHit)){
            //if (tempHit.shape == currentShape) {
            //    continue;
            //}
            if (tempHit.t < closestHit.t) {
                closestHit = tempHit;
                hitAnything = true;
                tmax = tempHit.t;
            }
        }
    }
    return hitAnything;
}

