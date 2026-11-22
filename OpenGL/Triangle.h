#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLSL.h"

// WIP for now
class Triangle {
    public:

    Triangle( glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

        std::vector<float> host_VertexBuffer = {
            v0.x, v0.y, v0.z,   normal.x, normal.y, normal.z,
            v1.x, v1.y, v1.z,   normal.x, normal.y, normal.z,
            v2.x, v2.y, v2.z,   normal.x, normal.y, normal.z,
        };

        int numBytes = host_VertexBuffer.size() * sizeof(float);

        GLuint m_VBO[1];
        GLuint m_VAO;

        //VBO stuff
        glGenBuffers(1, m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Clear vertex buffer
        host_VertexBuffer.clear();

        //VAO stuff
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glBindVertexArray(0);

    }


};