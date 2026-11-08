#pragma once

class Camera {
    public: 

    Camera();
    Camera(float near_val, float far_val, float field_of_view, float width, float height): near(near_val), far(far_val), fov(field_of_view), ip_width(width), ip_height(height) {}

    float near;
    float far;
    float fov;
    float ip_width;
    float ip_height;

};