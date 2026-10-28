#pragma once

#include "ISceneLoader.h"
#include "Scene.h"
#include <iostream>
#include <unordered_map>

class SceneLoader : public ISceneLoader {
private:
  Scene &m_targetScene; // Reference to the external scene

  std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

public:
  // The caller provides the scene to be filled
  SceneLoader(Scene &sceneToPopulate)
      : m_targetScene(sceneToPopulate), numShaders(0), numTextures(0) {}

  

  
  void reserveCameras(size_t count) override {
    // makes sure the vector has enough space
    int x = 1;
  }
  void reserveLights(size_t count) override {
    m_targetScene.lights.reserve(count);
  }
  void reserveShapes(size_t count) override {
    m_targetScene.shapes.reserve(count);
  }
  void reserveShaders(size_t count) override { numShaders = count; }
  void reserveTextures(size_t count) override { numTextures = count; }

  void setSceneParams(const SceneParams &sparams) override {
    std::cout << "Setting scene params." << std::endl;

    m_targetScene.bgColor = color(sparams.bgColor.x, sparams.bgColor.y, sparams.bgColor.z);
  }

  void addCamera(const std::string &name, const std::string &type,
                 const ISceneLoader::vec &pos, const ISceneLoader::vec &viewDir,
                 float focalLength, float imagePlaneWidth) override {
    std::cout << "Creating camera: " << name << ", type:" << type << std::endl;
    std::shared_ptr<Camera> camera = nullptr;
    if(type == "perspective" || type == "Perspective"){
      vec3 origin = vec3(pos.x,pos.y,pos.z);
      vec3 viewDirection = vec3(viewDir.x,viewDir.y,viewDir.z);
      camera = std::make_shared<PerspectiveCamera>(origin, viewDirection, focalLength, imagePlaneWidth, imagePlaneWidth);
    }
    m_targetScene.cam = camera;
  }
  void addPointLight(const ISceneLoader::vec &pos,
                     const ISceneLoader::vec &intensity) override {
    std::cout << "Creating point light." << std::endl;
    
    auto light = std::make_shared<PointLight>(vec3(pos.x,pos.y,pos.z), color(intensity.x,intensity.y,intensity.z));
    m_targetScene.lights.push_back(light);
  }
  void addAreaLight(const ISceneLoader::vec &pos,
                    const ISceneLoader::vec &color,
                    const ISceneLoader::vec &normal, float width,
                    float length) override {
    std::cout << "Creating area light." << std::endl;
  }
  void addShader(const ISceneLoader::ShaderDesc &shaderDesc) override {
    std::cout << "Creating shader: type=" << shaderDesc.type << std::endl;
    // I place my shaders on an unordered map often
    std::shared_ptr<Shader> shader = nullptr;
    if (shaderDesc.type == "lambertian" || shaderDesc.type == "Lambertian"){
      color col = color(shaderDesc.diffuse.data.x, shaderDesc.diffuse.data.y, shaderDesc.diffuse.data.z);
      shader = std::make_shared<Lambertian>(col);
    } else if (shaderDesc.type == "BlinnPhong" || shaderDesc.type == "blinnphong"){
      color spec = color(shaderDesc.specular.data.x, shaderDesc.specular.data.y, shaderDesc.specular.data.z);
      color diff = color(shaderDesc.diffuse.data.x, shaderDesc.diffuse.data.y, shaderDesc.diffuse.data.z);
      shader = std::make_shared<BlinnPhong>(shaderDesc.phongExp, diff, spec);
    } else if (shaderDesc.type == "Mirror" || shaderDesc.type == "mirror"){
      shader = std::make_shared<Mirror>();
    } else {
      shader = std::make_shared<NormalShader>();
    }

    shaders[shaderDesc.name] = shader;
  }
  void addShape(const ISceneLoader::ShapeDesc &shapeDesc) override {
    std::cout << "Creating shape: type=" << shapeDesc.type << std::endl;


    auto shader = shaders.find(shapeDesc.shaderNameReference);
    std::shared_ptr<Shader> assignedShader;

    if (shader != shaders.end()){
      assignedShader = shader->second;
    }

    std::shared_ptr<Shape> shape = nullptr;
    if (shapeDesc.type == "Sphere" || shapeDesc.type == "sphere"){
      point3 center = point3(shapeDesc.center.x, shapeDesc.center.y, shapeDesc.center.z);
      shape = std::make_shared<Sphere>(
        center, shapeDesc.radius, assignedShader
      );
    } else if (shapeDesc.type == "Triangle" || shapeDesc.type == "triangle"){
      vec3 a = vec3(shapeDesc.v0.x, shapeDesc.v0.y, shapeDesc.v0.z);
      vec3 b = vec3(shapeDesc.v1.x, shapeDesc.v1.y, shapeDesc.v1.z);
      vec3 c = vec3(shapeDesc.v2.x, shapeDesc.v2.y, shapeDesc.v2.z);
      shape = std::make_shared<Triangle>(
        a, b, c, assignedShader
      );
    }
    
    m_targetScene.shapes.push_back(shape);
  }
  void addTexture(const std::string &type, const std::string &name,
                  const std::string &sourceFile) override {
    std::cout << "Creating texture: type=" << type << ", name=" << name
              << ", sourceFile=" << sourceFile << std::endl;
  }

public:
  int numShaders;
  int numTextures;
};