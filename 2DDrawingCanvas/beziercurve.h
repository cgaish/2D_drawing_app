#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <iostream>
#include <string>

#include "constants.h"
#include "orthographiccamera.h"
#include "glshaderprogram.h"
#include "glshaderexception.h"

namespace Entity {

    class BezierCurve
    {
    public:
        BezierCurve();
        ~BezierCurve();
        void setupShaders();
        void setupGeometry();
        void setupMatrix();
        void update( float t );
        void draw();
        void resize(int, int);
    private:
        GLuint m_vbo; // 2 buffers for position and color handles
        GLuint m_posBufferHandle;
        GLuint m_colBufferHandle;
        GLuint m_vao;
        GLuint m_shaderProgramHandle;
        GLuint m_shaderProgramHandle2;
        GLShaderProgram m_shaderProgram;
        GLShaderProgram m_shaderProgram2;

        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 model;
        bool isOkay = false;

    };

}


#endif // BEZIERCURVE_H
