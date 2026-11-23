#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"
#include "OpenGLSceneLoader.h"
#include "../renderlib/SceneParser_JSON.h"

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

struct ShaderProgram {
    sivelab::GLSLObject glsl;
    GLint projMatrixID = -1, viewMatrixID = -1, modelMatrixID = -1, normalMatrixID = -1;
    GLint diffuseComponentID = -1, specCoefID = -1, phongExpID = -1;
    GLint lightPosWorldID = -1, lightIntensityID = -1, viewPosID = -1, viewDirID = -1;

    void init(const std::string& vertPath, const std::string& fragPath) {
        glsl.addShader(vertPath, sivelab::GLSLObject::VERTEX_SHADER);
        glsl.addShader(fragPath, sivelab::GLSLObject::FRAGMENT_SHADER);
        glsl.createProgram();
         projMatrixID       = glsl.createUniform("projMatrix");
        viewMatrixID       = glsl.createUniform("viewMatrix");
        modelMatrixID      = glsl.createUniform("modelMatrix");
        normalMatrixID     = glsl.createUniform("normalMatrix");
        diffuseComponentID = glsl.createUniform("diffuseComponent");
        specCoefID         = glsl.createUniform("specCoef");
        phongExpID         = glsl.createUniform("phongExp");
        lightPosWorldID    = glsl.createUniform("lightPosWorld");
        lightIntensityID   = glsl.createUniform("lightIntensity");
        viewPosID          = glsl.createUniform("viewPos");
        viewDirID          = glsl.createUniform("viewDir");
    }
};

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit()) {
        exit (-1);
    }
    
   
    // throw std::runtime_error("Error! initialization of glfw failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    int winWidth = 1000;
    float aspectRatio = 1.0; // 16.0 / 9.0; // winWidth / (float)winHeight;
    int winHeight = winWidth / aspectRatio;
    
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err=glewInit();
    if(err != GLEW_OK) {
        std::cerr <<"GLEW Error! glewInit failed, exiting."<< std::endl;
        exit(EXIT_FAILURE);
    }
    
    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    // JSON loading
    auto scene = std::make_shared<OpenGLSceneLoader>();
    SceneParser_JSON parser(scene);

    std::string filename = argv[1];
    parser.parseFileData(filename);

    glClearColor(scene->bgColor.r, scene->bgColor.g, scene->bgColor.b, 1.0f);

    glm::mat4 M_perspective = scene->projMatrix;

    // "default" light position in case anything wierd happens in the loader
    // (i.e. it's not given any light arguments)
    glm::vec4 lightPosWorld(1.0f, 2.0f, 1.0f, 1.0f);
    glm::vec3 lightIntensity(1.0f, 1.0f, 1.0f);
    if (!scene->lights.empty()) {
        lightPosWorld = glm::vec4(scene->lights[0].position, 1.0f);
        lightIntensity = scene->lights[0].intensity;
    }

    
    // shader stuff!
    std::string lambertianPath = std::string(SHADER_DIR) + "fragmentShader_Lambertian.glsl";
    std::string blinnPhongPath = std::string(SHADER_DIR) + "fragmentShader_BlinnPhong.glsl";
    std::string normalPath = std::string(SHADER_DIR) + "fragmentShader_Normal.glsl";
    std::string vertexPath_withMatrices = std::string(SHADER_DIR) + "vertexShader_PrepForPerFragment.glsl";
    

    std::unordered_map<std::string, ShaderProgram> programs;
    programs["BlinnPhong"].init(vertexPath_withMatrices, blinnPhongPath);
    programs["Phong"]      = programs["BlinnPhong"]; 
    programs["Lambertian"].init(vertexPath_withMatrices, lambertianPath);
    programs["Diffuse"]    = programs["Lambertian"];
    programs["Normal"].init(vertexPath_withMatrices, normalPath);

    glm::vec3 m_pos = scene->cameraPos;
    glm::vec3 m_U(scene->viewMatrix[0][0], scene->viewMatrix[1][0], scene->viewMatrix[2][0]);
    glm::vec3 m_V(scene->viewMatrix[0][1], scene->viewMatrix[1][1], scene->viewMatrix[2][1]);
    glm::vec3 m_W(scene->viewMatrix[0][2], scene->viewMatrix[1][2], scene->viewMatrix[2][2]);
    glm::vec3 m_viewDir = -m_W;

    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

    // Rendering loop
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 M_view = glm::lookAt(m_pos, m_pos - m_W, m_V);

        // draw all shapes
        for (const auto& [name, shape] : scene->shapes)
        {
            std::string shaderType = programs.count(shape.shader.type) ? shape.shader.type : "BlinnPhong";
            ShaderProgram& prog = programs[shaderType];

            prog.glsl.activate();

            // Camera & light uniforms
            if (prog.projMatrixID != -1)     glUniformMatrix4fv(prog.projMatrixID, 1, GL_FALSE, glm::value_ptr(M_perspective));
            if (prog.viewMatrixID != -1)     glUniformMatrix4fv(prog.viewMatrixID, 1, GL_FALSE, glm::value_ptr(M_view));
            if (prog.viewPosID != -1)        glUniform3fv(prog.viewPosID, 1, glm::value_ptr(m_pos));
            if (prog.viewDirID != -1)        glUniform3fv(prog.viewDirID, 1, glm::value_ptr(m_viewDir));
            if (prog.lightPosWorldID != -1)  glUniform4fv(prog.lightPosWorldID, 1, glm::value_ptr(lightPosWorld));
            if (prog.lightIntensityID != -1) glUniform3fv(prog.lightIntensityID, 1, glm::value_ptr(lightIntensity));

            glm::mat4 M_model  = shape.modelMatrix;
            glm::mat4 M_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(M_model))));

            glm::vec3 diffuse(shape.shader.diffuse.data.x,
                              shape.shader.diffuse.data.y,
                              shape.shader.diffuse.data.z);
            glm::vec3 specular(shape.shader.specular.data.x,
                               shape.shader.specular.data.y,
                               shape.shader.specular.data.z);

            if (prog.modelMatrixID != -1)      glUniformMatrix4fv(prog.modelMatrixID, 1, GL_FALSE, glm::value_ptr(M_model));
            if (prog.normalMatrixID != -1)     glUniformMatrix4fv(prog.normalMatrixID, 1, GL_FALSE, glm::value_ptr(M_normal));
            if (prog.diffuseComponentID != -1) glUniform3fv(prog.diffuseComponentID, 1, glm::value_ptr(diffuse));
            if (prog.specCoefID != -1)         glUniform3fv(prog.specCoefID, 1, glm::value_ptr(specular));
            if (prog.phongExpID != -1)         glUniform1f(prog.phongExpID, shape.shader.phongExp);

            glBindVertexArray(shape.mesh.VAO);
            glDrawArrays(GL_TRIANGLES, 0, shape.mesh.vertexCount);

            prog.glsl.deactivate();
        }

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();


        // Camera movement (can add more later if I feel like it)
        float moveRatePerFrame = 0.05f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            m_pos = m_pos + -m_W * moveRatePerFrame;
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            m_pos = m_pos - m_U * moveRatePerFrame;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            m_pos = m_pos + m_W * moveRatePerFrame;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            m_pos = m_pos + m_U * moveRatePerFrame;
        }

        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0 / timeDiff << std::endl;
        }


        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    glfwTerminate();
    return 0;
}


