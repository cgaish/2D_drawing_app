#ifndef GEO_H
#define GEO_H

#include <iostream>
#include <vector>
#include <random>
#include <QDebug>
#include <QTime>

#include "constants.h"
#include "random.h"
#include "texture.h"
#include "Camera.h"
#include "grid.h"
#include "particleutils.h"
#include "glshaderprogram.h"
#include "glshaderexception.h"

#define MAX_BEZ_POINTS pow(2,8)
#define BEZIER_MAX_ERROR 4.0f
#define BEZIER_MIN_ERROR 0.0125f
#define BEZIER_RENDER_ERROR 0.05f


namespace Entity {

    class Geo
    {
    public:
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
            void setPointSize(int size);
            int getPointCount();
            int getPointShaderID();
            void draw();
        private:
            GLuint m_vao;
            GLuint m_vbo;
            GLuint m_shaderProgramHandle;
            GLShaderProgram m_shaderProgram;

            int m_pointCount = 0;
            std::vector<glm::vec3> m_pointPosition;
            std::vector<glm::vec3> m_pointColor;
            std::vector<float> m_pointSize;

        };

        class CubicCurve
        {
        public:
            CubicCurve();
            ~CubicCurve();
            void setupShaders();
            void setupGeometry();
            void setupMatrix();
            void update();
            void draw();

            GLuint m_vbo[2] = {0}; // 2 buffers for position and color handles
            GLuint m_posBufferHandle;
            GLuint m_colBufferHandle;
            GLuint m_vao;
            GLuint m_shaderProgramHandle;
            GLShaderProgram m_lineShaderProgram;
            GLShaderProgram m_pointShaderProgram;
            glm::mat4 model, view, projection;
        };

        class Quad{
        public:
            Quad();
            ~Quad();

            void setupShaders();
            void setupGeometry();
            void setupMatrix();
            void update();
            void draw();

            GLuint m_vbo; // 1 buffer for position
            GLuint m_posBufferHandle;
            GLuint m_colBufferHandle;
            GLuint m_vao;
            GLuint m_shaderProgramHandle;
            GLShaderProgram m_quadShaderProgram;
            glm::mat4 model, view, projection;
        };

        class Triangles{
        public:
            Triangles();
            ~Triangles();

            void setupShaders();
            void setupGeometry();
            void setupMatrix();
            void update();
            void draw();
        private:
            GLuint m_vbo; // 1 buffer for position
            GLuint m_posBufferHandle;
            GLuint m_colBufferHandle;
            GLuint m_vao;
            GLuint m_shaderProgramHandle;
            GLShaderProgram m_quadShaderProgram;
            glm::mat4 model, view, projection;
        };

        class Particles{
        public:
            Particles();
            ~Particles();
            void setupShaders();
            void setupGeometry();
            void setMatrices(GLShaderProgram &p);
            void update(float t);
            void draw();
            float randFloat();
            void resize(int w, int h);
        private:
            int width, height;
            Grid grid;
            Random rand;
            glm::mat4 model, view, projection;
            float angle, time, particleLifetime;
            // Position and direction of particle emitter
            glm::vec3 emitterPos, emitterDir;
            GLShaderProgram renderProg, flatProg;
            GLuint initVel, startTime, particles, nParticles;

        };

        class Circle{
        public:
            Circle();
            ~Circle();
            void setupShaders();
            void setupGeometry();
            void setMatrices(GLShaderProgram &p);
            void update(float t);
            void draw();
            float randFloat();
            void resize(int w, int h);
        private:
            int width, height;
            GLuint vao, vbo;
            glm::mat4 model, view, projection;
            // Position and direction of particle emitter
            GLShaderProgram renderProg, flatProg;

        };

        class Curve{
        public:
            Curve();
            ~Curve();
            void setupShaders();
            void setupGeometry();
            void setMatrices();
            void update(float t);
            void draw();
            float randFloat();
            void setScreenSize(int x, int y);
            void resize(int w, int h);
            std::vector <float> convertPointstoNdc(float *a, int sizeOfArray);
        private:
            int width, height;
            std::vector<float> quadCurve;
            std::vector <glm::vec2> result;
            int sizeOfArray;
            glm::vec2 screenSize;
            GLuint m_vao, m_vbo;
            GLuint m_vao_curve, m_vbo_curve;
            GLuint m_pointShaderProgramHandle, m_lineShaderProgramHandle;
            glm::mat4 model, view, projection;
            std::vector<int> screenResolution;
            // Position and direction of particle emitter
            GLShaderProgram m_pointShaderProgram, m_lineShaderProgram;

        };

        Geo();
    };

}


#endif // GEO_H
