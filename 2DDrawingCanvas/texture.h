#ifndef TEXTURE_H
#define TEXTURE_H

#include <QDebug>
#include "constants.h"
#include <string>
#include "stb-master/stb_image.h"
class Texture {
public:
    static GLuint loadTexture( const std::string & fName );
    static GLuint loadCubeMap(const std::string & baseName, const std::string & extention = ".png");
    static GLuint loadHdrCubeMap( const std::string & baseName );
    static unsigned char * loadPixels( const std::string & fName, int & w, int & h, bool flip = true );
    static void deletePixels( unsigned char * );
};

#endif // TEXTURE_H
