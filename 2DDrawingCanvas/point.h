#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

#include "constants.h"
#include "orthographiccamera.h"
#include "glshaderprogram.h"
#include "glshaderexception.h"

namespace Entity {

    class Point
    {
    public:
        Point();
        ~Point();
        void setupShaders();
        void setupGeometry();
        void setupMatrix(const char *name, const glm::mat4 &m);
        void update();
        void setPointCoord(glm::vec3 coord);
        void setPointColor(glm::vec3 color);
        int getPointCount() { return m_pointCount; }
        void draw();
    private:
        GLuint m_vbo[2] = {0}; // 2 buffers for position and color handles
        GLuint m_posBufferHandle;
        GLuint m_colBufferHandle;
        GLuint m_vao;
        GLuint m_shaderProgramHandle;
        GLShaderProgram m_shaderProgram;

        int m_pointCount = 0;
        std::vector<glm::vec3> m_pointGeo;
        std::vector<glm::vec3> m_pointColor;

    };
}



#endif // POINT_H
