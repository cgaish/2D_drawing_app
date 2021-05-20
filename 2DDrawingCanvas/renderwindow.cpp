#include "renderwindow.h"

RenderWindow::RenderWindow(QWidget *parent) : QOpenGLWidget(parent)
{

}

RenderWindow::~RenderWindow()
{
    uninitializeGL();
}

void RenderWindow::initializeGL()
{
    if(!gladLoadGL()){
        qDebug() << "Unable to load OpenGL functions" << "\n";
        exit(EXIT_FAILURE);
    }
    getOpenGLInfo();
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
}

void RenderWindow::paintGL()
{

}

void RenderWindow::uninitializeGL()
{
    // Delete all pointers and opengl context
}

void RenderWindow::getOpenGLInfo()
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

std::string RenderWindow::getShaderInfoLog(GLuint shader) {
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

std::string RenderWindow::getProgramInfoLog(GLuint program)
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

const char* RenderWindow::getTypeString(GLint datatype)
{
    //return std::to_string(datatype);
}

void RenderWindow::setupShaders()
{
    // Vertex shader
    qDebug() << "Compiling Shader Program";
    std::ifstream inFile("../OGLTestpad/vertex.glsl");
    if(!inFile) {
        fprintf(stderr, "Error opening file: vertex.glsl\n");
        exit(1);
    }
    // Load content
    std::stringstream code;
    code << inFile.rdbuf();
    inFile.close();
    std::string codeStr(code.str());

    // Create the shader object
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    if(0 == vertShader){
        std::cerr << "Error creating vertex shader." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Load the source code into the shader object
    const GLchar* codeArray[] = { codeStr.c_str() };
    glShaderSource(vertShader, 1, codeArray, NULL);

    // Compile the shader
    glCompileShader(vertShader);

    // Check the compilation status
    GLint result;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    if(GL_FALSE == result){
        std::cerr << "Vertex shader compilation failed!" << std::endl;
        std::cerr << getShaderInfoLog(vertShader) << std::endl;
        exit(EXIT_FAILURE);
    }

    // ===========================================================================

    // Load contents of file into shaderCode here
    std::ifstream fragFile("../OGLTestpad/fragment.glsl");
    if (!fragFile) {
        fprintf(stderr, "Error opening file: fragment.glsl\n");
        exit(1);
    }

    std::stringstream fragCode;
    fragCode << fragFile.rdbuf();
    fragFile.close();
    codeStr = fragCode.str();

    // Create the shader object
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (0 == fragShader) {
        fprintf(stderr, "Error creating fragment shader.\n");
        exit(1);
    }

    // Load the source code into the shader object
    codeArray[0] = codeStr.c_str();
    glShaderSource(fragShader, 1, codeArray, NULL);

    // Compile the shader
    glCompileShader(fragShader);

    // Check compilation status
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result) {
        std::cerr << "Fragment shader compilation failed!" << std::endl;
        std::cerr << getShaderInfoLog(vertShader) << std::endl;
        exit(EXIT_FAILURE);
    }

    // ===========================================================================

    linkShaders(vertShader, fragShader);
}

void RenderWindow::linkShaders(GLint vertShader, GLint fragShader)
{
    // Create the program object
   programHandle = glCreateProgram();
   if(0 == programHandle) {
       std::cerr << "Error creating program object." << std::endl;
       exit(EXIT_FAILURE);
   }

   // Bind index 0 to the shader input variable "VertexPosition"
   glBindAttribLocation(programHandle, 0, "VertexPosition");
   // Bind index 1 to the shader input variable "VertexColor"
   glBindAttribLocation(programHandle, 1, "VertexColor");

   // Attach the shaders to the program object
   glAttachShader( programHandle, vertShader );
   glAttachShader( programHandle, fragShader );

   // Link the program
   glLinkProgram( programHandle );

   // Check for successful linking
   GLint status;
   glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
   if (GL_FALSE == status) {
       std::cerr << "Failed to link shader program!" << std::endl;
       std::cerr << getProgramInfoLog(programHandle) << std::endl;
       exit(EXIT_FAILURE);
   }

   // Clean up shader objects
   glDetachShader(programHandle, vertShader);
   glDetachShader(programHandle, fragShader);
   glDeleteShader(vertShader);
   glDeleteShader(fragShader);

   glUseProgram( programHandle );
}

void RenderWindow::setupGeometry()
{

}

void RenderWindow::mousePressEvent(QMouseEvent *event)
{
    xPos = event->x();
    yPos = event->y();

    test += 0.1f;
    qDebug() << "XPOS at press: " << xPos << "YPOS at press: " << yPos;
    geo.push_back(test);
    geo.push_back(test);
    geo.push_back(0.0f);

    if(geo.size() >=3){
        setupGeometry();
        setupShaders();
        paintGL();
    }
}

void RenderWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int xPosAtRelease = event->x();
    int yPosAtRelease = event->y();

    int dx = xPosAtRelease - xPos;
    int dy = yPosAtRelease - yPos;
    qDebug() << "XPOS at release: " << dx << "YPOS at release: " << dy;
}


