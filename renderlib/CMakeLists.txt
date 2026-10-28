add_library(renderlib 
    vec3.h
    color.h
    Framebuffer.h Framebuffer.cpp
    ray.h
    Camera.h Camera.cpp
    PerspectiveCamera.h PerspectiveCamera.cpp
    hittable.h 
    Shape.h Shape.cpp
    Sphere.h Sphere.cpp
    Triangle.h Triangle.cpp
    Scene.h Scene.cpp
    PointLight.h
    Shader.h
    Lambertian.h Lambertian.cpp
    NormalShader.h NormalShader.cpp
    BlinnPhong.h BlinnPhong.cpp
    Functions.h Functions.cpp
    Mirror.h Mirror.cpp
    SceneLoader.h 
    ISceneLoader.h
    SceneParser_JSON.h SceneParser_JSON.cpp
)

target_include_directories(renderlib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

target_link_libraries(renderlib PRIVATE
    PNG::PNG
    ZLIB::ZLIB
    OpenMP::OpenMP_CXX
    nlohmann_json::nlohmann_json
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(renderlib PRIVATE OpenMP::OpenMP_CXX)
endif()

set_target_properties(renderlib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(mainCode
    mainCode.cpp
)

target_link_libraries(mainCode 
    PRIVATE 
        renderlib 
        PNG::PNG
        ZLIB::ZLIB
        OpenMP::OpenMP_CXX
        nlohmann_json::nlohmann_json
)






