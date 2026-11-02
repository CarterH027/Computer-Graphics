#pragma once

#include "Shape.h"
#include "BoundingBox.h"
#include <algorithm>
#include <memory>
#include <vector>


class bvhNode : public Shape {


    public: 
    bvhNode() : leftChild(nullptr), rightChild(nullptr) {}
    bvhNode(std::vector<std::shared_ptr<Shape>>& shapes, int AXIS);

    bool intersect(const ray& r, float tmin, float& tmax, HitRecord& hit) override;
    const BoundingBox& getBox() override;
    vec3 centroid() override;

    private:

    BoundingBox bbox;
    std::shared_ptr<Shape> leftChild;
    std::shared_ptr<Shape> rightChild;

    BoundingBox mergeBoundingBoxes(const BoundingBox &b0, const BoundingBox &b1);
};