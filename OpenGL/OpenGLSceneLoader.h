#pragma once

#include "../renderlib/ISceneLoader.h"
#include "Camera.h"
#include "Mesh.h"

#include <cmath>
#include <iostream>

#include <unordered_map>

struct GLLight {
  glm::vec3 position;
  glm::vec3 intensity;
};

struct Shape {
    Mesh mesh;
    glm::mat4 modelMatrix{1.0f};
    ISceneLoader::ShaderDesc shader;
};

class OpenGLSceneLoader : public ISceneLoader {
    
public:
    Camera camera = Camera(0.1f, 1000.0f, 45.0, 15.0f, 15.0f);
    glm::vec3 cameraPos{0.0f};
    glm::vec3 bgColor{0.5f, 0.7f, 1.0f};
    glm::mat4 viewMatrix{1.0f};
    glm::mat4 projMatrix{1.0f};
    float aspectRatio = 1.0f;

    std::vector<GLLight> lights;
    std::unordered_map<std::string, ShaderDesc> shaders;
    std::unordered_map<std::string, Shape> shapes;


    void reserveCameras(size_t count) override {}
    void reserveLights(size_t count) override { lights.reserve(count); }
    void reserveShapes(size_t count) override { shapes.reserve(count); }
    void reserveShaders(size_t count) override { shaders.reserve(count); }
    void reserveTextures(size_t count) override {}



    void setSceneParams(const SceneParams& params) override {
        std::cout << "Setting scene params." << std::endl;

        bgColor = glm::vec3(params.bgColor.x, params.bgColor.y, params.bgColor.z);
    }

    void addAreaLight(const vec &pos, const vec &color, const vec &normal,
                      float width, float length) override {
        addPointLight(pos, color);
    }

    void addTexture(const std::string &type, const std::string &name,
                    const std::string &sourceFile) override {}

    void addCamera(const std::string &name, const std::string &type,
                 const vec &pos, const vec &viewDir, float focalLength,
                 float imagePlaneWidth) override {
        float ipWidth = imagePlaneWidth;
        float ipHeight = imagePlaneWidth;

        float fov = 2.0f * std::atan((ipHeight * 0.5f) / focalLength);

        camera = Camera(0.1f, 1000.0f, fov, ipWidth, ipHeight);
        cameraPos = {pos.x, pos.y, pos.z};

        glm::vec3 dir = glm::normalize(glm::vec3(viewDir.x, viewDir.y, viewDir.z));
        viewMatrix = glm::lookAt(cameraPos, cameraPos + dir, {0.0f, 1.0f, 0.0f});

        projMatrix = glm::perspective(camera.fov, camera.ip_width / camera.ip_height, camera.near, camera.far);
    }

    void addPointLight(const vec &pos, const vec &intensity) override {
        lights.push_back({{pos.x, pos.y, pos.z}, {intensity.x, intensity.y, intensity.z}});
    }

    void addShader(const ShaderDesc& shaderDesc) override {
        shaders[shaderDesc.name] = shaderDesc;
    }

    void addShape(const ShapeDesc &desc) override {
        Shape shape;
        shape.shader = shaders[desc.shaderNameReference];
        glm::mat4 baseXform = desc.hasXForm ? desc.localXForm : glm::mat4(1.0f);


        if (shaders.count(desc.shaderNameReference)) {
            shape.shader = shaders[desc.shaderNameReference];
        }


        if (desc.type == "sphere") {
            shape.mesh = getOrCreateUnitSphere();
            shape.modelMatrix = baseXform * glm::translate(glm::mat4(1.0f), {desc.center.x, desc.center.y, desc.center.z}) *
                                glm::scale(glm::mat4(1.0f), glm::vec3(desc.radius));
        } else if (desc.type == "triangle") {
            shape.mesh = createTriangle({desc.v0.x, desc.v0.y, desc.v0.z},
                                        {desc.v1.x, desc.v1.y, desc.v1.z},
                                        {desc.v2.x, desc.v2.y, desc.v2.z});
            shape.modelMatrix = baseXform;             
        }

        std::string key = desc.name.empty() ? ("shape_" + std::to_string(shapes.size())) : desc.name;
        shapes[key] = shape;
    }

    private:
    Mesh unitSphere{0, 0, 0};

    Mesh getOrCreateUnitSphere() {
        if (unitSphere.VAO == 0) {
            unitSphere = createSphere(1.0f, 3);
        }
        return unitSphere;
    }



};
