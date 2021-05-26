#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

// Cpp Libs
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// Constants
#include <constants.h>

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

#include "Camera.h"
#include "orthographiccamera.h"
#include "glshaderprogram.h"
#include "point.h"
#include "beziercurve.h"

class RenderManager : public QOpenGLWidget
{
    Q_OBJECT
public:
    // OpenGL specific variables
    QString openGLInfo;
    bool beginDrawing = false;

public:
    explicit RenderManager(QWidget *widget = nullptr);
    ~RenderManager();
    void getOpenGLInfo();
    void uninitializeGL();
    std::string getShaderInfoLog(GLuint shader);
    std::string getProgramInfoLog(GLuint program);
    const char* getTypeString(GLint datatype);

    void setupEntity();
    void calculateAngle( float t );
    void checkDebugContext();

protected:
    void initializeGL() override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void printAllVariables();
//    void resizeEvent(QResizeEvent* ev) override {
//        resizeGL(width(), height());
//    }
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
    // variables
    int m_pointCount = 1;
    double xPos, yPos, zPos=0;
    float starting_x = 0.0f;
    float starting_y = 0.0f;


    // Class variables
    OrthographicCamera m_CameraOrtho;
    GLShaderProgram m_pointShaderProgram;
    Entity::Point m_point;
    Entity::BezierCurve m_bcurve;




signals:

};

#endif // RENDERMANAGER_H
