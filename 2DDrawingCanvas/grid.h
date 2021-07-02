#ifndef GRID_H
#define GRID_H
#include "constants.h"
#include "drawable.h"

#include <vector>

class Grid : public Drawable {
private:
    std::vector<GLuint> buffers;
    GLuint vao;
    GLsizei nVerts;

public:
    Grid( float size = 10.0f, int nDivisions = 10 );
    virtual ~Grid();
    void render() const override;
};
#endif // GRID_H
