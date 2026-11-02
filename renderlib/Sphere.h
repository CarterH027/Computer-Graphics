#pragma once

#include "hittable.h"
#include "Shape.h"
#include "NormalShader.h"
#include "BoundingBox.h"

class Sphere : public Shape {

    public: 
    Sphere(): center(vec3(0,0,0)), radius(1.0), shader(std::make_shared<NormalShader>()) {computeBox();}
    Sphere(point3 center, float radius): center(center), radius(radius), shader(std::make_shared<NormalShader>()) {computeBox();}
    Sphere(point3 center, float radius, std::shared_ptr<Shader> shader): center(center), radius(radius), shader(shader){computeBox();}

    bool intersect(const ray& r, float tmin, float& tmax, HitRecord& hit) override;
    const BoundingBox& getBox() override;

    vec3 centroid() {return center;}
    private:
    void computeBox() {
        point3 min_corner = center - vec3(radius, radius, radius);
        point3 max_corner = center + vec3(radius, radius, radius);
        bbox = BoundingBox(min_corner.x(), max_corner.x(), min_corner.y(), max_corner.y(), min_corner.z(), max_corner.z());
    }

    std::shared_ptr<Shader> shader;
    point3 center;
    float radius;
    BoundingBox bbox;

};