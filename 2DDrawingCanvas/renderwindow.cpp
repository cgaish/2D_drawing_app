#include "renderwindow.h"

RenderWindow::RenderWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    qDebug() << "Render window size: " << this->width() << " | " << this->height();
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
    checkDebugContext();
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    // To draw points this must be initialized
    glEnable(GL_PROGRAM_POINT_SIZE);
    // Query point size range
    GLfloat sizeRange[2] = {0.0f};
    glGetFloatv(GL_POINT_SIZE_RANGE, sizeRange);
    qDebug() << "Point size range: " << sizeRange[0] << sizeRange[1];

    // Setup shaders and geometry
    setupShaders();
    setupGeometry();
}

void RenderWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_POINTS, 0, 3 );
    glBindVertexArray(0);
}

void RenderWindow::uninitializeGL()
{
    // Delete all pointers and opengl context
}

void RenderWindow::setupShaders()
{
    // Vertex shader
    qDebug() << "Compiling Shader Program";
    std::ifstream inFile("../2DDrawingCanvas/basic.vert");
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
    std::ifstream fragFile("../2DDrawingCanvas/basic.frag");
    if (!fragFile) {
        fprintf(stderr, "Error opening file: basic.frag\n");
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
    /////////////////// Create the VBO ////////////////////
       float positionData[] = {
               0.0f,  0.0f, 0.0f,
               0.8f, -0.8f, 0.0f,
               0.0f,  0.8f, 0.0f
       };
       float colorData[] = {
               1.0f, 0.0f, 0.0f,
               1.0f, 0.0f, 0.0f,
               1.0f, 0.0f, 0.0f
       };


       // Create and populate the buffer objects
       glGenBuffers(2, vboHandles);
       positionBufferHandle = vboHandles[0];
       colorBufferHandle = vboHandles[1];

       glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
       glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

       glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
       glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

       // Create and set-up the vertex array object
       glGenVertexArrays( 1, &vaoHandle );
       glBindVertexArray(vaoHandle);

       glEnableVertexAttribArray(0);  // Vertex position
       glEnableVertexAttribArray(1);  // Vertex color

       glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
       glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );

       glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
       glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
       glBindVertexArray(0);

}

void RenderWindow::checkDebugContext()
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

void RenderWindow::mousePressEvent(QMouseEvent *event)
{
    xPos = event->x();
    yPos = event->y();

    test += 0.1f;
    qDebug() << "XPOS at press: " << xPos << "YPOS at press: " << yPos;
    geo.push_back(test);
    geo.push_back(test);
    geo.push_back(0.0f);

}

void RenderWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int xPosAtRelease = event->x();
    int yPosAtRelease = event->y();

    int dx = xPosAtRelease - xPos;
    int dy = yPosAtRelease - yPos;
    qDebug() << "XPOS at release: " << dx << "YPOS at release: " << dy;
}

void RenderWindow::glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
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

