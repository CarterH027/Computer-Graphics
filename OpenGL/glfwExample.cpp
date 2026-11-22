#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

#include "Camera.h"
#include "Mesh.h"

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

int main(void)
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
    glClearColor(0.0f, 0.0f, 0.0f, 1);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    
    Camera cam = Camera(0.1f, 1000.0f, 45.0, 15.0f, 15.0f);
    // Need to set a projection matrix that fits the aspect ratio set
    // by the window frame.
    //
    // The ortho parameters, in order: left, right, bottom, top, zNear, zFar
    float halfWidth = cam.ip_width / 2.0;
    float halfHeight = cam.ip_height / 2.0;

    float left = -halfWidth;
    float right = halfWidth;

    float bottom = -halfHeight;
    float top = halfHeight;

    glm::mat4 M_ortho = glm::ortho(left, right, bottom, top, cam.near, cam.far);

    // The perspective parameters

    glm::mat4 M_perspective = glm::perspective(glm::radians(cam.fov), cam.ip_width/cam.ip_height, cam.near, cam.far);

    // Model Matrices
    float rotAngle = 0.0f;
    glm::mat4 rot = glm::mat4(1.0);
    rot = glm::rotate(rot, rotAngle, glm::vec3(0, 1, 0));

    float x, y, z;
    x = 0.0f;
    y = 0.0f; 
    z = 0.0f;
    glm::vec3 translation_vec = glm::vec3(x, y, z);
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), translation_vec);

    float sx, sy, sz;
    sx = 1.0f;
    sy = 1.0f;
    sz = 1.0f;
    glm::vec3 scale_vec = glm::vec3(sx, sy, sz);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), scale_vec);

    glm::mat4 M_model = trans * rot * scale;


    //Normal matrix
    glm::mat4 M_normal = glm::mat4(glm::transpose(glm::inverse(glm::mat3(M_model))));

    //I don't know how this ended up here honestly but here it is
    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

    // create a Vertex Array Buffer to hold our triangle data 
    //GLuint m_triangleVBO[1];
    //GLuint m_VAO;
                                                  
    //glGenBuffers(1, m_triangleVBO);
    //glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    // this is the actual triangle data that will be copied to                                              
    // the GPU memory     
    
    // hard coded triangle code for now
    //glm::vec3 v0(-3.0f, -3.0f, 0.0f);
    //glm::vec3 v1(3.0f, -3.0f, 0.0f);
    //glm::vec3 v2(0.0f, 3.0f, 0.0f);

    //normals for hard coded single triangle
    //glm::vec3 edge1 = v1 - v0;
    //glm::vec3 edge2 = v2 - v0;
    //glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

    //float normal_x = normal.x;
    //float normal_y = normal.y;
    //float normal_z = normal.z;

    //std::vector< float > host_VertexBuffer{
    //    v0.x, v0.y, v0.z,  normal_x, normal_y, normal_z,// V0                                    
    //    v1.x, v1.y, v1.z,  normal_x, normal_y, normal_z,// V1                                    
    //    v2.x, v2.y, v2.z,  normal_x, normal_y, normal_z,// V2
    //};                                   

    //int numBytes = host_VertexBuffer.size() * sizeof(float);

    // Triangle color
    //glm::vec3 diffuseComponent(1.0f, 0.0f, 0.0f);
    //glm::vec3 specCoeff(1.0f, 1.0f, 1.0f);
    //glm::float32 phongExp(64.0f);

    // copy the numBytes from host_VertexBuffer t the GPU and store in                                      
    // the currently bound VBO                                                                              
    //glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // once copied, we no longer need the data on the host                                                  
    //host_VertexBuffer.clear();  

    // create a vertex array object that will map the attributes in                                         
    // our vertex buffer to different location attributes for our                                           
    // shaders                                                                                              
    //glGenVertexArrays(1, &m_VAO);
    //glBindVertexArray(m_VAO);

    // VAO details here - we only have 1 attribute or location                                              
    // (Position of the vertex)                                                                             
    //glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glBindVertexArray(0);
    
    glm::vec3 diffuseComponent(1.0f, 0.0f, 0.0f);
    glm::vec3 specCoeff(1.0f, 1.0f, 1.0f);
    glm::float32 phongExp(64.0f);

    Mesh sphere = createSphere(1.0f, 8);


    //Light
    glm::vec4 lightPosWorld(1.0f, 2.0f, 1.0f, 1.0f);
    glm::vec3 lightIntensity(1.0f, 1.0f, 1.0f);

    // Create a shader using my GLSLObject class                                                            
    sivelab::GLSLObject shader;

    std::string lambertianPath = std::string(SHADER_DIR) + "fragmentShader_Lambertian.glsl";
    std::string blinnPhongPath = std::string(SHADER_DIR) + "fragmentShader_BlinnPhong.glsl";
    std::string normalPath = std::string(SHADER_DIR) + "fragmentShader_Normal.glsl";
    std::string vertexPath_withMatrices = std::string(SHADER_DIR) + "vertexShader_PrepForPerFragment.glsl";

    shader.addShader(vertexPath_withMatrices, sivelab::GLSLObject::VERTEX_SHADER);
    shader.addShader( lambertianPath, sivelab::GLSLObject::FRAGMENT_SHADER );
    //shader.addShader( blinnPhongPath, sivelab::GLSLObject::FRAGMENT_SHADER );
    //shader.addShader( normalPath, sivelab::GLSLObject::FRAGMENT_SHADER );

    shader.createProgram();

    GLuint projMatrixID, viewMatrixID, modelMatrixID, normalMatrixID;
    projMatrixID = shader.createUniform( "projMatrix" );
    viewMatrixID = shader.createUniform( "viewMatrix" );
    modelMatrixID = shader.createUniform( "modelMatrix" );
    normalMatrixID = shader.createUniform( "normalMatrix" );
    
    GLuint diffuseComponentID, lightPosWorldID, specCoefID, phongExpID, viewPosID, viewDirID, lightIntensityID;
    diffuseComponentID = shader.createUniform( "diffuseComponent" );
    lightPosWorldID = shader.createUniform( "lightPosWorld" );
    specCoefID = shader.createUniform( "specCoef" );
    phongExpID = shader.createUniform( "phongExp" );
    viewPosID = shader.createUniform( "viewPos" );
    viewDirID = shader.createUniform( "viewDir" );
    lightIntensityID = shader.createUniform( "lightIntensity" );


    glm::vec3 m_pos(0,0,0), m_viewDir(0,0,-1);
    glm::vec3 m_U(1,0,0), m_V(0,1,0), m_W(0,0,1);

    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;
    
    /* Loop until the user closes the window */

    
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        // Clear the window's buffer (or clear the screen to our
        // background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 M_view = glm::lookAt( m_pos, m_pos - m_W, m_V );

        /* Render your objects here */
        shader.activate();

        // copy from the host to the device the view matrix and the projection matrix                                                                                       
        //glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr( M_ortho ));
        glUniform3fv(viewPosID, 1, glm::value_ptr(m_pos));
        glUniform3fv(viewDirID, 1, glm::value_ptr(m_viewDir));
        glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr( M_perspective));
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr( M_view ));
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr( M_model));
        glUniformMatrix4fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr( M_normal ));
        glUniform4fv(lightPosWorldID, 1, glm::value_ptr(lightPosWorld));
        glUniform3fv(lightIntensityID, 1, glm::value_ptr(lightIntensity));
        glUniform3fv(diffuseComponentID, 1, glm::value_ptr(diffuseComponent));
        glUniform3fv(specCoefID, 1, glm::value_ptr(specCoeff));
        glUniform1f(phongExpID, phongExp);

    
        glBindVertexArray(sphere.VAO);
        glDrawArrays(GL_TRIANGLES, 0, sphere.vertexCount);
        glBindVertexArray(0);

        shader.deactivate();

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        float moveRatePerFrame = 0.05;

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

        if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS) {
            std::cout << "fps: " << 1.0/timeDiff << std::endl;
        }
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }
  
    glfwTerminate();
    return 0;
}
