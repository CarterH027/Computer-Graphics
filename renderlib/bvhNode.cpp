#include "bvhNode.h"
#include <algorithm>
#include <memory>
#include <vector>


bvhNode::bvhNode(std::vector<std::shared_ptr<Shape>>& shapes, int AXIS) {
    unsigned int N = shapes.size();

    
    if (N == 1) {
        leftChild = shapes[0];
        rightChild = nullptr;
        bbox = shapes[0]->getBox();
    } else if (N == 2) {
        leftChild = shapes[0];
        rightChild = shapes[1];
        bbox = mergeBoundingBoxes(shapes[0]->getBox(), shapes[1]->getBox());
    } else {
        std::sort(shapes.begin(), shapes.end(),
            [AXIS](const std::shared_ptr<Shape> a,
                   const std::shared_ptr<Shape> b) {
                return (a->centroid()[AXIS] < b->centroid()[AXIS]);
            });

        std::vector<std::shared_ptr<Shape>> leftside(shapes.begin(), shapes.begin() + (N/2));
        std::vector<std::shared_ptr<Shape>> rightside(shapes.begin() + (N/2), shapes.end());

        leftChild = std::make_shared<bvhNode>(
            leftside, (AXIS + 1) % 3
        );
        rightChild = std::make_shared<bvhNode>(
            rightside, (AXIS + 1) % 3
        );

        bbox = mergeBoundingBoxes(leftChild->getBox(), rightChild->getBox());
    }
};

BoundingBox bvhNode::mergeBoundingBoxes(const BoundingBox &b0, const BoundingBox &b1) {
    return BoundingBox(
        std::min(b0.x_min, b1.x_min), std::max(b0.x_max, b1.x_max),
        std::min(b0.y_min, b1.y_min), std::max(b0.y_max, b1.y_max),
        std::min(b0.z_min, b1.z_min), std::max(b0.z_max, b1.z_max)
    );

}

bool bvhNode::intersect(const ray& r, float tmin, float& tmax, HitRecord& hit) {
    HitRecord tempHit;
    float temp_tmax = tmax;

    if (!bbox.intersect(r, tmin, temp_tmax, tempHit)) {
        return false;
    }

    bool hit_left = leftChild ? leftChild->intersect(r, tmin, tmax, hit) : false;

    bool hit_right = rightChild ? rightChild->intersect(r, tmin, tmax, hit) : false;

    return hit_left || hit_right;
}

const BoundingBox& bvhNode::getBox() {
    return bbox;
}

vec3 bvhNode::centroid() {
    return vec3(
        (bbox.x_min + bbox.x_max) * 0.5f,
        (bbox.y_min + bbox.y_max) * 0.5f,
        (bbox.z_min + bbox.z_max) * 0.5f
    );
}
