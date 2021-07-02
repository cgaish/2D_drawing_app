#include "rendermanager.h"
#include "glshaderexception.h"
#include <algorithm>

RenderManager::RenderManager(QWidget *parent) : QOpenGLWidget(parent),
                m_CameraOrtho(NDC_MIN, NDC_MAX, NDC_MIN, NDC_MAX) { }

RenderManager::~RenderManager()
{
    uninitializeGL();
}

void RenderManager::initializeGL()
{
    qDebug() << "/////////////////// Initializing OpenGL ////////////////////";

    if(!gladLoadGL()){
        qDebug() << "Unable to load OpenGL functions" << "\n";
        exit(EXIT_FAILURE);
    }
    getOpenGLInfo();
    checkDebugContext();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMinSampleShading(0.5f);
    glClearColor(BACKGROUND_COLOR[0],
                 BACKGROUND_COLOR[1],
                 BACKGROUND_COLOR[2],
                 BACKGROUND_COLOR[3]);





    // Setup shaders and geometry
    //setupEntity();
//    Entity::Geo::CubicCurve* curve1 = new Entity::Geo::CubicCurve();
//    curve1->setupShaders();
//    curve1->setupGeometry();
//    curve1->setupMatrix();
//    geoCurve.push_back(curve1);
//    int count = 10000;
//    for(int i = 0; i < count ; i++){
//        Entity::Geo::Point *point = new Entity::Geo::Point;
//        point->setPointColor(POINT_COLOR);
//        point->setPointCoord(glm::vec3(0.0, 0.0, 0.0));

//        point->setupGeometry();
//        point->setupShaders();

//        geoPoint.push_back(point);
//    }

    //point1.setupMatrix();

//    Entity::Geo::Quad quad;
//    quad.setupShaders();
//    quad.setupGeometry();
//    //quad.setupMatrix();
//    geoQuad.push_back(quad);
//    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
//    Entity::Geo::Point *point = new Entity::Geo::Point;
//    glm::vec3 newPosition = generateRandomPosition();
//    glm::mat4 trans = glm::mat4(1.0f);
//    trans = glm::translate(trans, glm::vec3(-0.5f, -0.3f, 0.0f));



//    point->setPointCoord(glm::vec3(-0.5, -0.5, 0.0));
//    point->setPointCoord(glm::vec3(0.5, -0.5, 0.0));
//    point->setPointCoord(glm::vec3(0.5, 0.5, 0.0));
//    point->setPointCoord(glm::vec3(-0.5, 0.5, 0.0));
//    point->setPointColor(RED);
//    point->setPointColor(GREEN);
//    point->setPointColor(BLUE);
//    point->setPointColor(YELLOW);

//    point->setupGeometry();
//    point->setupShaders();
//    //point->setupMatrix("u_MVPMatrix", trans);
//    geoPoint.push_back(point);

//    Entity::Geo::Triangles *tri = new Entity::Geo::Triangles;
//    tri->setupShaders();
//    tri->setupGeometry();
//    geoTriangles.push_back(tri);

//    Entity::Geo::Particles *p = new Entity::Geo::Particles();
//    geoParticles.push_back(p);
    //p->setupShaders();
    //p->setupGeometry();

//    Entity::Geo::Circle *circle1 = new Entity::Geo::Circle();
//    circle1->setupShaders();
//    circle1->setupGeometry();
//    geoCircle.push_back(circle1);

    Entity::Geo::Curve *curve1 = new Entity::Geo::Curve();
    curve1->setupShaders();
    curve1->setupGeometry();
    Curve.push_back(curve1);

}

void RenderManager::paintGL()
{
    qDebug() << "/////////////////// Drawing ////////////////////";
    printAllVariables();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Curve[0]->draw();
    //createPrimitive();
    //geoPoint[0]->draw();
    //geoTriangles[0]->draw();
//    geoParticles[0]->draw();
//    geoCurve[0]->draw();
//    for(auto &elem : geoPoint){
//        elem->draw();
//    }


}

void RenderManager::uninitializeGL()
{
    // Delete all pointers and opengl context
}

void RenderManager::checkDebugContext()
{
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if( flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        qDebug() << "///////////////// Debug context initialized! //////////////////";
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}

void RenderManager::mousePressEvent(QMouseEvent *event)
{

    qDebug() << "/////////////////// Mouse Click Event ////////////////////";
    // Get screen click coordinates
    //xPos = event->x();
    //yPos = event->y();

    // Define NDC values
    //float max_ndc = +1.0f;
    //float min_ndc = -1.0f;
    //float offset = 2;

    // Calculate NDC
    //float pPosX = min_ndc + offset * xPos / this->width();
    //float pPosY = max_ndc - offset * yPos / this->height();
    //float pPosZ = 1.0f;

    // Update with new point NDC coordinates
    //glm::vec3 pointCoord = glm::vec3(pPosX, pPosY, pPosZ);
    //m_point.setPointCoord(pointCoord);

    // Update point color values for new point
    //m_point.setPointColor(POINT_COLOR);

    // Update point count
    //m_pointCount = m_point.getPointCount();

    // Pass new data to openGL
    //m_point.setupMatrix("u_MVPMatrix", m_CameraOrtho.GetViewProjectionMatrix());
    //m_point.update();

    // Set draw to true
    if( !beginDrawing )
        beginDrawing = true;

    // Draw

}

void RenderManager::mouseReleaseEvent(QMouseEvent *event)
{
    int xPosAtRelease = event->x();
    int yPosAtRelease = event->y();

    int dx = xPosAtRelease - xPos;
    int dy = yPosAtRelease - yPos;
    qDebug() << "XPOS at release: " << dx << "YPOS at release: " << dy;
}

void RenderManager::mouseMoveEvent(QMouseEvent *event)
{
    float starting_x = 0.0f;
    float starting_y = 0.0f;
    if( event->buttons() == Qt::LeftButton ){
        if( event->x() >= 600)
            starting_x += 0.1f;
        else
            starting_x -= 0.1f;

        if( event->y() >= 300)
            starting_y -= 0.1f;
        else
            starting_y += 0.1f;
        m_CameraOrtho.SetPosition({starting_x,starting_y,0.0f});
        //m_pointShaderProgram.setUniform("u_MVPMatrix", m_CameraOrtho.GetViewProjectionMatrix());
       // m_pointShaderProgram.use();
        //update();
        qDebug() << "Dragging..... "<< event->x() << " | "<< event->y();
        //m_viewerCamera->ProcessMouseMovement(event->x(), event->y());
    }
    else
        qDebug() << "No Dragging..... ";
    update();
}

void RenderManager::glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
{
    // ignore non-significant error/warning codes
        if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        std::cout << "---------------" << std::endl;
        std::cout << "Debug message (" << id << "): " <<  message << std::endl;

        switch (source)
        {
            case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
            case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
            case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
        } std::cout << std::endl;

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
            case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
            case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
            case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
            case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
            case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
            case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
        } std::cout << std::endl;

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
            case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
            case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
        } std::cout << std::endl;
        std::cout << std::endl;
}

void RenderManager::getOpenGLInfo()
{
    QString openGLInfo;
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Renderer         : %s\n", renderer);
    printf("GL Vendor           : %s\n", vendor);
    printf("GL Version          : %s\n", version);
    printf("GL Version No.      : %d.%d\n", major, minor);
    printf("GLSL Version        : %s\n", glslVersion);

}

std::string RenderManager::getShaderInfoLog(GLuint shader) {
    GLint logLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

    std::string log;
    if (logLen > 0) {
        log.resize(logLen, ' ');
        GLsizei written;
        glGetShaderInfoLog(shader, logLen, &written, &log[0]);
    }

    return log;
}

std::string RenderManager::getProgramInfoLog(GLuint program)
{
    GLint logLen;
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLen );

    std::string log;
    if (logLen > 0) {
       log.resize(logLen, ' ');
       GLsizei written;
       glGetProgramInfoLog(program, logLen, &written, &log[0]);
    }
    return log;
}

void RenderManager::printAllVariables(){
    qDebug() << "\n";
    qDebug() << "/////////////////// Printing Variables Data ////////////////////";
    qDebug() << " --------------------------------------------------------------------- ";
    //qDebug() << "| Point geo size: " << m_pointGeo.size() << "                           |";
    //qDebug() << "| Point col size: " << m_pointColor.size() << "                           |";
    qDebug() << " --------------------------------------------------------------------- ";
    qDebug() << "\n";

}

glm::vec3 RenderManager::generateRandomPosition()
{

    srand (static_cast <unsigned> (time(0)));
    float x = -1.0 + static_cast<float>(rand()) / (static_cast <float> (RAND_MAX/(1.0-(-1.0))));
    float y = -1.0 + static_cast<float>(rand()) / (static_cast <float> (RAND_MAX/(1.0-(-1.0))));


    qDebug() << "x is : " << x;
    qDebug() << "y is : " << y;
    return glm::vec3(x, y, 0.0f);
}

void RenderManager::createPrimitive()
{
//    m_pointCount += 1;
//    Entity::Geo::Point *point = new Entity::Geo::Point;
//    point->setPointColor(POINT_COLOR);
//    point->setupGeometry();
//    point->setupShaders();
//    point->draw();
//    //geoPoint.push_back(point);
//    update();
//    qDebug() << "Point count: " << m_pointCount;
}


