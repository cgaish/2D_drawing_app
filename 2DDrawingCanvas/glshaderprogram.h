///////////////////////////////// OpenGL Shader Class //////////////////////////////////
// This class is responsible for all tasks related to reading shader code from file   //
// or string, processing them, compiling linking and then creating a shader program   //
// handle, to pass to OpenGL. It also defines function related to getting uniforms    //
// and other variables defined inside the shader , it can fetch and assign data to    //
// GLSL shader's in/out variables etc.                                                //
////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLSHADERPROGRAM_H
#define GLSHADERPROGRAM_H

#include "constants.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <sys/stat.h>


// Shader types
namespace GLShader {

    enum ShaderType {
        VERTEX          = GL_VERTEX_SHADER,
        FRAGMENT        = GL_FRAGMENT_SHADER,
        GEOMETRY        = GL_GEOMETRY_SHADER,
        TESS_CONTROL    = GL_TESS_CONTROL_SHADER,
        TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
        COMPUTE         = GL_COMPUTE_SHADER
    };

}

class GLShaderProgram
{
private:
    GLuint m_programHandle;
    bool m_linked;
    std::string m_logString;

    int  getUniformLocation(const char * name );
    bool fileExists( const std::string & fileName );

public:
    GLShaderProgram();

    bool   compileShaderFromFile( const char * fileName, GLShader::ShaderType type );
    bool   compileShaderFromString( const std::string & source, GLShader::ShaderType type );
    bool   link();
    bool   validate();
    void   use();

    std::string log();

    int    getHandle();
    bool   isLinked();

    void   bindAttribLocation( GLuint location, const char * name);
    void   bindFragDataLocation( GLuint location, const char * name );

    void   setUniform( const char *name, float x, float y, float z);
    void   setUniform( const char *name, const glm::vec2 & v);
    void   setUniform( const char *name, const glm::vec3 & v);
    void   setUniform( const char *name, const glm::vec4 & v);
    void   setUniform( const char *name, const glm::mat3 & m);
    void   setUniform( const char *name, const glm::mat4 & m);
    void   setUniform( const char *name, float val );
    void   setUniform( const char *name, int val );
    void   setUniform( const char *name, bool val );

    void   printActiveUniforms();
    void   printActiveAttribs();

};

#endif // GLSHADERPROGRAM_H
