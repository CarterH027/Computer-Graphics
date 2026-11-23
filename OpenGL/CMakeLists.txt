include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/renderlib    
)

add_executable (glfwExample
  glfwExample.cpp 
  GLSL.cpp GLSL.h
  Camera.h
  Mesh.h
  OpenGLSceneLoader.h
)

target_link_libraries (glfwExample PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwExample PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample PRIVATE OpenGL::GL)
endif()

target_compile_definitions(glfwExample PRIVATE SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Shaders/")

target_link_libraries (glfwExample PRIVATE PNG::PNG)
target_link_libraries (glfwExample PRIVATE ZLIB::ZLIB)

add_executable (main
  main.cpp 
  GLSL.cpp GLSL.h
  Camera.h
  Mesh.h
  OpenGLSceneLoader.h
  ${CMAKE_SOURCE_DIR}/renderlib/SceneParser_JSON.cpp
)

target_link_libraries (main PRIVATE GLEW::GLEW)
target_link_libraries (main PRIVATE glfw)
target_link_libraries (main PRIVATE nlohmann_json::nlohmann_json) 

if(APPLE)
    target_link_libraries(main PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(main PRIVATE OpenGL::GL)
endif()

target_compile_definitions(main PRIVATE SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Shaders/")

target_link_libraries (main PRIVATE PNG::PNG)
target_link_libraries (main PRIVATE ZLIB::ZLIB)




