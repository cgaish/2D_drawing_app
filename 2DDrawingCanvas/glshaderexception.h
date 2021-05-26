#ifndef GLSHADEREXCEPTION_H
#define GLSHADEREXCEPTION_H

#include <iostream>
#include <string>

class GLShaderException : public std::runtime_error
{
public:
    GLShaderException( const std::string &msg ) :
        std::runtime_error(msg) {};
};

#endif // GLSHADEREXCEPTION_H
