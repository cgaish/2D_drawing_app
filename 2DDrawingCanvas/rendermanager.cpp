#include "rendermanager.h"
#include "glshaderexception.h"

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
    glClearColor(BACKGROUND_COLOR[0],
                 BACKGROUND_COLOR[1],
                 BACKGROUND_COLOR[2],
                 BACKGROUND_COLOR[3]);

    // To draw points this must be initialized
    glEnable(GL_PROGRAM_POINT_SIZE);

    // Setup shaders and geometry
    setupEntity();

}

void RenderManager::setupEntity()
{
    // Setup Point Entity
    m_point.setupGeometry();
    m_point.setupShaders();
    m_point.setupMatrix("u_MVPMatrix", m_CameraOrtho.GetViewProjectionMatrix()); // Camera


}

void RenderManager::paintGL()
{
    qDebug() << "/////////////////// Drawing ////////////////////";
    printAllVariables();
    glClear(GL_COLOR_BUFFER_BIT);

    if( beginDrawing )
        m_point.draw();

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
    xPos = event->x();
    yPos = event->y();

    // Define NDC values
    float max_ndc = +1.0f;
    float min_ndc = -1.0f;
    float offset = 2;

    // Calculate NDC
    float pPosX = min_ndc + offset * xPos / this->width();
    float pPosY = max_ndc - offset * yPos / this->height();
    float pPosZ = 1.0f;

    // Update with new point NDC coordinates
    glm::vec3 pointCoord = glm::vec3(pPosX, pPosY, pPosZ);
    m_point.setPointCoord(pointCoord);

    // Update point color values for new point
    m_point.setPointColor(POINT_COLOR);

    // Update point count
    m_pointCount = m_point.getPointCount();

    // Pass new data to openGL
    m_point.setupMatrix("u_MVPMatrix", m_CameraOrtho.GetViewProjectionMatrix());
    m_point.update();

    // Set draw to true
    if( !beginDrawing )
        beginDrawing = true;

    // Draw
    update();
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

const char* RenderManager::getTypeString(GLint datatype)
{
    //return std::to_string(datatype);
}

void RenderManager::printAllVariables(){
    qDebug() << "\n";
    qDebug() << "/////////////////// Printing Variables Data ////////////////////";
    qDebug() << " --------------------------------------------------------------------- ";
    qDebug() << "| Point count: " << m_point.getPointCount() << "                           |";
    //qDebug() << "| Point geo size: " << m_pointGeo.size() << "                           |";
    //qDebug() << "| Point col size: " << m_pointColor.size() << "                           |";
    qDebug() << " --------------------------------------------------------------------- ";
    qDebug() << "\n";

}

