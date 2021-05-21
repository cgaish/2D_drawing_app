#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

// Cpp Libs
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// Third party OpenGL Libs
#include <glad.h>
// GLM
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"


// Qt OpenGL Libs
#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QMouseEvent>
#include <QString>
#include <QDebug>

// Qt Utility Libs
#include <QString>
#include <QLatin1String>
#include <QDebug>
#include <QString>


class RenderWindow : public QOpenGLWidget
{
    Q_OBJECT
public:
    // OpenGL specific variables
    QString openGLInfo;
    float angle;
    glm::mat4 rotationMatrix;

public:
    explicit RenderWindow(QWidget *widget = nullptr);
    ~RenderWindow();
    void getOpenGLInfo();
    void uninitializeGL();
    std::string getShaderInfoLog(GLuint shader);
    std::string getProgramInfoLog(GLuint program);
    const char* getTypeString(GLint datatype);
    void setupShaders();
    void linkShaders(GLint vertShader, GLint fragShader);
    void setupGeometry();
    void calculateAngle( float t );
    void checkDebugContext();

protected:
    void initializeGL() override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    static void APIENTRY glDebugOutput(
            GLenum source,
            GLenum type,
            unsigned int id,
            GLenum severity,
            GLsizei length,
            const char* message,
            const void* userParam
            );

private:
    // cpp variables
    double xPos, yPos, zPos=0;
    std::vector<float> geo;
    float test = 0.0f;

    // OpenGL variables
    GLuint vaoHandle;
    GLuint vboHandles[2];
    GLuint programHandle;
    GLuint positionBufferHandle;
    GLuint colorBufferHandle;

signals:

};

#endif // RENDERWINDOW_H
