#pragma once

#include "hittable.h"
#include "Shape.h"
#include "NormalShader.h"
#include "BoundingBox.h"
#include <algorithm>

class Triangle : public Shape {

    public:
    Triangle(): point_a(vec3(0,0,0)), point_b(vec3(1,0,0)), point_c(vec3(0,1,0)), shader(std::make_shared<NormalShader>()) {}
    Triangle(const vec3& a, const vec3& b, const vec3& c) : point_a(a), point_b(b), point_c(c), shader(std::make_shared<NormalShader>()) {}
    Triangle(const vec3& a, const vec3& b, const vec3& c, std::shared_ptr<Shader> shader) : point_a(a), point_b(b), point_c(c), shader(shader) {}

    bool intersect(const ray& r, float tmin, float& tmax, HitRecord& hit) override;
    const BoundingBox& getBox() override;


    vec3 centroid() {return (point_a + point_b + point_c) / 3.0f;}
    
    private:

    void computeBox() {
        float xmin = std::min({point_a.x(), point_b.x(), point_c.x()});
        float xmax = std::max({point_a.x(), point_b.x(), point_c.x()});
        
        float ymin = std::min({point_a.y(), point_b.y(), point_c.y()});
        float ymax = std::max({point_a.y(), point_b.y(), point_c.y()});
        
        float zmin = std::min({point_a.z(), point_b.z(), point_c.z()});
        float zmax = std::max({point_a.z(), point_b.z(), point_c.z()});

        float delta = 0.00001;
        if (xmax - xmin < delta) {
            xmin -= delta;
            xmax += delta;
        }
        if (ymax - ymin < delta) {
            ymin -= delta;
            ymax += delta;
        }
        if (zmax - zmin < delta) {
            zmin -= delta;
            zmax += delta;
        }

        bbox = BoundingBox(xmin, xmax, ymin, ymax, zmin, zmax);
    }
    
    std::shared_ptr<Shader> shader;
    point3 point_a, point_b, point_c;
    BoundingBox bbox;

};