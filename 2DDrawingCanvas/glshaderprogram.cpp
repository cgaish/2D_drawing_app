#include "glshaderprogram.h"


// Constructor
GLShaderProgram::GLShaderProgram() : m_programHandle(0), m_linked(false) { }

// Get uniform location in shader program from its name
int GLShaderProgram::getUniformLocation(const char *name)
{
    return glGetUniformLocation( m_programHandle, name );
}

// System utility function for file check
bool GLShaderProgram::fileExists(const std::string &fileName)
{
    struct stat info;
    int ret = -1;

    ret = stat(fileName.c_str(), &info);
    return 0 == ret;
}

/* This function takes two params a pointer to shader file object and shader type enum,
It checks if the file is readable and data is their in it , process it then pass it to
string shader function which further compiles it to shader program understood by OpenGL */

bool GLShaderProgram::compileShaderFromFile(const char *fileName, GLShader::ShaderType type)
{

    ///////////////////////// Error checks //////////////////////////////

    // Check if file doesnt exist return false
    if ( ! fileExists(fileName) )
    {
        m_logString = "File not found.";
        return false;
    }

    // Check if no handle create one, if not created return false
    if( m_programHandle <= 0 ) {
        m_programHandle = glCreateProgram();
        if( m_programHandle == 0 ) {
            m_logString = "Unable to create shader program.";
            return false;
        }
    }

    // Check if shader file can be read else return false
    std::ifstream inShaderFile( fileName, std::ios::in );
    if( !inShaderFile ) {
        return false;
    }

    ///////////////////////// Process Shader File //////////////////////////////

    std::ostringstream shaderCode; // To store string format of shader file content
    // Until there is something to read
    while( inShaderFile.good() ) {
        // get each character and dump in shaderCode var
        int c = inShaderFile.get();
        if( !inShaderFile.eof() )
            shaderCode << (char) c;
    }
    // Close the file when done
    inShaderFile.close();

    ///////////////////////// Return Result //////////////////////////////

    // return the shaderCode variable in string format and type of shader
    return compileShaderFromString(shaderCode.str(), type);

}

/* This function takes two arguments shader code string and shader type, creates a program
handle and a shader handle based on shader type, passes the code to opengl and initiates the
compiling process, it also gathers the compiler log for any error while compiling the shaders
finally attach the compiled shader handle to program handle returns true if done */

bool GLShaderProgram::compileShaderFromString(const std::string &source, GLShader::ShaderType type)
{
    ///////////////////////// Checks //////////////////////////////

    // Check if program handle is not created
    if( m_programHandle <= 0 ) {
        // Create one if not
        m_programHandle = glCreateProgram();
        // Check if still handle is not created
        if( m_programHandle == 0 ){
            // Report and return false if failed.
            m_logString = "Unable to create shader program.";
            return false;
        }
    }

    // Check shader type and create shader handle accordingly
    GLuint shaderHandle = 0;
    switch ( type ) {
    case GLShader::ShaderType::VERTEX:
        shaderHandle = glCreateShader(GL_VERTEX_SHADER);
        break;
    case GLShader::ShaderType::FRAGMENT:
        shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    case GLShader::ShaderType::GEOMETRY:
        shaderHandle = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    case GLShader::ShaderType::TESS_CONTROL:
        shaderHandle = glCreateShader(GL_TESS_CONTROL_SHADER);
        break;
    case GLShader::ShaderType::TESS_EVALUATION:
        shaderHandle = glCreateShader(GL_TESS_EVALUATION_SHADER);
        break;
    default:
        return false;
    }

    ///////////////////////// Processing //////////////////////////////

    // Get shader code in C string format since opengl requires a pointer to c string
    const char * c_code = source.c_str();
    glShaderSource( shaderHandle, 1, &c_code, NULL);

    // Compile the shader
    glCompileShader( shaderHandle );

    // Check for compilation errors
    int result;
    glGetShaderiv( shaderHandle, GL_COMPILE_STATUS, &result );
    // Check if result is true or not
    if( GL_FALSE == result ) {
        // Compile failed
        int length = 0;
        m_logString = "";
        glGetShaderiv( shaderHandle, GL_INFO_LOG_LENGTH, &length );
        if( length > 0 ) {
            char *c_log = new char[length];
            int written = 0;
            glGetShaderInfoLog( shaderHandle, length, &written, c_log );
            m_logString = c_log;
            delete [] c_log;
        }
        return false;
    } else {
        // Compile succeeded , attach shader and return
        glAttachShader( m_programHandle, shaderHandle );
        return true;
    }
}

bool GLShaderProgram::link()
{
    if( m_linked ) return true;
        if( m_programHandle <= 0 ) return false;

        glLinkProgram(m_programHandle);

        int status = 0;
        glGetProgramiv( m_programHandle, GL_LINK_STATUS, &status);
        if( GL_FALSE == status ) {
            // Store log and return false
            int length = 0;
            m_logString = "";

            glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &length );

            if( length > 0 ) {
                char * c_log = new char[length];
                int written = 0;
                glGetProgramInfoLog(m_programHandle, length, &written, c_log);
                m_logString = c_log;
                delete [] c_log;
            }

            return false;
        } else {
            m_linked = true;
            return m_linked;
        }
}

bool GLShaderProgram::validate()
{
    if( ! isLinked() ) return false;

        GLint status;
        glValidateProgram( m_programHandle );
        glGetProgramiv( m_programHandle, GL_VALIDATE_STATUS, &status );

        if( GL_FALSE == status ) {
            // Store log and return false
            int length = 0;
            m_logString = "";

            glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &length );

            if( length > 0 ) {
                char * c_log = new char[length];
                int written = 0;
                glGetProgramInfoLog(m_programHandle, length, &written, c_log);
                m_logString = c_log;
                delete [] c_log;
            }

            return false;
        } else {
           return true;
        }
}

void GLShaderProgram::use()
{
    if( m_programHandle <= 0 || (! m_linked) ) return;
    glUseProgram( m_programHandle );
}

std::string GLShaderProgram::log()
{
    return m_logString;
}

int GLShaderProgram::getHandle()
{
    return m_programHandle;
}

bool GLShaderProgram::isLinked()
{
    return m_linked;
}

void GLShaderProgram::bindAttribLocation(GLuint location, const char *name)
{
    glBindAttribLocation( m_programHandle, location, name );
}

void GLShaderProgram::bindFragDataLocation(GLuint location, const char *name)
{
    glBindFragDataLocation( m_programHandle, location, name );
}

void GLShaderProgram::setUniform(const char *name, float x, float y, float z)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 ) {
        glUniform3f(loc,x,y,z);
    } else {
        printf("Uniform: %s not found.\n",name);
    }
}

void GLShaderProgram::setUniform(const char *name, const glm::vec2 &v)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 ) {
        glUniform2f(loc,v.x,v.y);
    } else {
        printf("Uniform: %s not found.\n",name);
    }
}

void GLShaderProgram::setUniform(const char *name, const glm::vec3 &v)
{
    this->setUniform( name, v.x, v.y, v.z );
}

void GLShaderProgram::setUniform(const char *name, const glm::vec4 &v)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 ) {
        glUniform4f(loc,v.x,v.y,v.z,v.w);
    } else {
        printf("Uniform: %s not found.\n",name);
    }
}

void GLShaderProgram::setUniform(const char *name, const glm::mat3 &m)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
    } else {
        printf("Uniform: %s not found.\n",name);
    }
}

void GLShaderProgram::setUniform(const char *name, const glm::mat4 &m)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
    } else {
        printf("Uniform: %s not found.\n",name);
    }
}

void GLShaderProgram::setUniform(const char *name, float val)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniform1f(loc, val);
    } else {
        printf("Uniform: %s not found.\n",name);
    }
}

void GLShaderProgram::setUniform(const char *name, int val)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniform1i(loc, val);
    } else {
        printf("Uniform: %s not found.\n",name);
    }
}

void GLShaderProgram::setUniform(const char *name, bool val)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniform1i(loc, val);
    } else {
        printf("Uniform: %s not found.\n",name);
    }
}

void GLShaderProgram::printActiveUniforms()
{
    GLint nUniforms, size, location, maxLen;
    GLchar * name;
    GLsizei written;
    GLenum type;

    glGetProgramiv( m_programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
    glGetProgramiv( m_programHandle, GL_ACTIVE_UNIFORMS, &nUniforms);

    name = (GLchar *) malloc( maxLen );

    printf(" Location | Name\n");
    printf("------------------------------------------------\n");
    for( int i = 0; i < nUniforms; ++i ) {
        glGetActiveUniform( m_programHandle, i, maxLen, &written, &size, &type, name );
        location = glGetUniformLocation(m_programHandle, name);
        printf(" %-8d | %s\n",location, name);
    }

    free(name);
}

void GLShaderProgram::printActiveAttribs()
{
    GLint written, size, location, maxLength, nAttribs;
    GLenum type;
    GLchar * name;

    glGetProgramiv(m_programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
    glGetProgramiv(m_programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);

    name = (GLchar *) malloc( maxLength );

    printf(" Index | Name\n");
    printf("------------------------------------------------\n");
    for( int i = 0; i < nAttribs; i++ ) {
        glGetActiveAttrib( m_programHandle, i, maxLength, &written, &size, &type, name );
        location = glGetAttribLocation(m_programHandle, name);
        printf(" %-5d | %s\n",location, name);
    }

    free(name);
}


