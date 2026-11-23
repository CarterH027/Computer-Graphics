#pragma once 

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



#include <vector>

struct Mesh{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int vertexCount;
};

void subdivide(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
               int depth, float R, std::vector<float>& buffer){
        
        if (depth == 0) {
            glm::vec3 n0 = glm::normalize(v0);
            glm::vec3 n1 = glm::normalize(v1);
            glm::vec3 n2 = glm::normalize(v2);

            buffer.push_back(v0.x); buffer.push_back(v0.y), buffer.push_back(v0.z);
            buffer.push_back(n0.x); buffer.push_back(n0.y); buffer.push_back(n0.z);

            buffer.push_back(v1.x); buffer.push_back(v1.y); buffer.push_back(v1.z);
            buffer.push_back(n1.x); buffer.push_back(n1.y); buffer.push_back(n1.z);

            buffer.push_back(v2.x); buffer.push_back(v2.y); buffer.push_back(v2.z);
            buffer.push_back(n2.x); buffer.push_back(n2.y); buffer.push_back(n2.z);

            return;
        }

        glm::vec3 v0v1 = glm::normalize((v0 + v1) / 2.0f) * R;
        glm::vec3 v1v2 = glm::normalize((v1 + v2) / 2.0f) * R;
        glm::vec3 v2v0 = glm::normalize((v2 + v0) / 2.0f) * R;

        subdivide(v0,   v0v1, v2v0, depth - 1, R, buffer);
        subdivide(v0v1, v1,   v1v2, depth - 1, R, buffer);
        subdivide(v2v0, v1v2, v2,   depth - 1, R, buffer);
        subdivide(v0v1, v1v2, v2v0, depth - 1, R, buffer);
}

// Icosahedron constants and logic partially made with help from Google AI
Mesh createSphere(float R, int depth) { 
    const float X = 0.525731112119133606f;
    const float Z = 0.850650808352039932f;
    const float N = 0.0f;

    // Icosahedron base vertices and faces -- for subdivision
    std::vector<glm::vec3> baseVertices = {
        glm::vec3(-X,  N,  Z) * R, glm::vec3( X,  N,  Z) * R,
        glm::vec3(-X,  N, -Z) * R, glm::vec3( X,  N, -Z) * R,
        glm::vec3( N,  Z,  X) * R, glm::vec3( N,  Z, -X) * R,
        glm::vec3( N, -Z,  X) * R, glm::vec3( N, -Z, -X) * R,
        glm::vec3( Z,  X,  N) * R, glm::vec3(-Z,  X,  N) * R,
        glm::vec3( Z, -X,  N) * R, glm::vec3(-Z, -X,  N) * R
    };

    std::vector<std::vector<int>> faces = {
        {0, 1, 4},  {0, 4, 9},  {9, 4, 5},  {4, 8, 5},  {4, 1, 8},
        {8, 1, 10}, {8, 10, 3}, {5, 8, 3},  {5, 3, 2},  {2, 3, 7},
        {7, 3, 10}, {7, 10, 6}, {7, 6, 11}, {11, 6, 0}, {0, 6, 1},
        {6, 10, 1}, {9, 11, 0}, {9, 2, 11}, {9, 5, 2},  {7, 11, 2}
    };

    std::vector<float> vertices;
    for (int i = 0; i < 20; ++i) {
        int idx0 = faces[i].at(0);
        int idx1 = faces[i].at(1);
        int idx2 = faces[i].at(2);

        subdivide(baseVertices.at(idx0),
                    baseVertices.at(idx1),
                    baseVertices.at(idx2),
                    depth, R, vertices);
    }

    for (int i = 0; i < 20; ++i) {
        for (int j =0; j < 3; ++j) {
            int cornerIndex = faces[i][j];
            vertices.push_back(baseVertices[cornerIndex][0]);
            vertices.push_back(baseVertices[cornerIndex][1]);
            vertices.push_back(baseVertices[cornerIndex][2]);
        }
    }

    Mesh mesh;
    mesh.vertexCount = vertices.size() / 6;

    glGenBuffers(1, &mesh.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return mesh;
}

Mesh createTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
    glm::vec3 n = glm::normalize(glm::cross(v1 - v0, v2 - v0));

    std::vector<float> vertices = {
        v0.x, v0.y, v0.z,  n.x, n.y, n.z,
        v1.x, v1.y, v1.z,  n.x, n.y, n.z,
        v2.x, v2.y, v2.z,  n.x, n.y, n.z
    };

    Mesh mesh;
    mesh.vertexCount = 3;

    glGenBuffers(1, &mesh.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return mesh;
}
