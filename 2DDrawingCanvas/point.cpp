#include "point.h"

Entity::Point::Point()
{

}

Entity::Point::~Point()
{

}

void Entity::Point::setupShaders()
{
    try {
        m_shaderProgram.compileShaderFromFile("../2DDrawingCanvas/basic.vert",
                                                 GLShader::ShaderType::VERTEX );
        m_shaderProgram.compileShaderFromFile("../2DDrawingCanvas/basic.frag",
                                                 GLShader::ShaderType::FRAGMENT);

        m_shaderProgram.link();
        m_shaderProgram.validate();
        m_shaderProgram.use();
    }  catch ( GLShaderException &e ) {
        std::cerr << e.what() << std::endl;
    }

    m_shaderProgramHandle = m_shaderProgram.getHandle();
}

void Entity::Point::setupGeometry()
{
    if( m_vbo[0] == 0 ){
        glGenBuffers(2, m_vbo);
        m_posBufferHandle = m_vbo[0];
        m_colBufferHandle = m_vbo[1];
        glGenVertexArrays( 1, &m_vao );
    }


    qDebug() << "/////////////////// Setting Up Point Geometry ////////////////////";

    // Create and populate the buffer objects

    glBindBuffer(GL_ARRAY_BUFFER, m_posBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_pointCount, m_pointGeo.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_colBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_pointCount, m_pointColor.data(), GL_STATIC_DRAW);

    // Create and set-up the vertex array object

    glBindVertexArray(m_vao);

    glEnableVertexAttribArray(0);  // Vertex position
    glEnableVertexAttribArray(1);  // Vertex color

    glBindBuffer(GL_ARRAY_BUFFER, m_posBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLubyte *)NULL );

    glBindBuffer(GL_ARRAY_BUFFER, m_colBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLubyte *)NULL );
}

void Entity::Point::setupMatrix(const char *name, const glm::mat4& m)
{
    m_shaderProgram.setUniform(name, m);
}

void Entity::Point::update()
{
    setupGeometry();
}

void Entity::Point::setPointCoord(glm::vec3 coord)
{
    m_pointGeo.push_back(coord);
    m_pointCount++;
}

void Entity::Point::setPointColor(glm::vec3 color)
{
    m_pointColor.push_back(color);
}

void Entity::Point::draw()
{
    glUseProgram(m_shaderProgramHandle);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_POINTS, 0, m_pointGeo.size() );
    glBindVertexArray(0);
}
