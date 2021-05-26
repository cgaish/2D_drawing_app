#include "beziercurve.h"

Entity::BezierCurve::BezierCurve()
{
    qDebug() << "/////////////////// Bez Curve Init ////////////////////";
}

Entity::BezierCurve::~BezierCurve()
{

}

void Entity::BezierCurve::setupShaders()
{
    qDebug() << "/////////////////// Bez Curve Setup Shaders ////////////////////";
    try {
        m_shaderProgram.compileShaderFromFile("../2DDrawingCanvas/bez.vs",
                                                 GLShader::ShaderType::VERTEX );
        m_shaderProgram.compileShaderFromFile("../2DDrawingCanvas/bez.fs",
                                                 GLShader::ShaderType::FRAGMENT);
        m_shaderProgram.compileShaderFromFile("../2DDrawingCanvas/bez.tes",
                                                 GLShader::ShaderType::TESS_EVALUATION);
        m_shaderProgram.compileShaderFromFile("../2DDrawingCanvas/bez.tcs",
                                                 GLShader::ShaderType::TESS_CONTROL);

        isOkay = m_shaderProgram.link();
        if( isOkay)
            qDebug() << "bez shader linked!";
        isOkay = m_shaderProgram.validate();
        if( isOkay)
            qDebug() << "bez shader validated!";
        m_shaderProgram.use();
        m_shaderProgram.setUniform("NumSegments", 50);
        m_shaderProgram.setUniform("NumStrips", 1);
        m_shaderProgram.setUniform("LineColor", glm::vec4(1.0f,1.0f,0.5f,1.0f));
        m_shaderProgramHandle = m_shaderProgram.getHandle();

        m_shaderProgram2.compileShaderFromFile("../2DDrawingCanvas/cps.vs",
                                         GLShader::ShaderType::VERTEX );
        m_shaderProgram2.compileShaderFromFile("../2DDrawingCanvas/cps.fs",
                                         GLShader::ShaderType::FRAGMENT);
        m_shaderProgram2.link();
        if( isOkay)
            qDebug() << "cps shader linked!";
        m_shaderProgram2.validate();
        if( isOkay)
            qDebug() << "cps shader validated!";
        m_shaderProgram2.use();
        m_shaderProgramHandle2 = m_shaderProgram.getHandle();
    }  catch ( GLShaderException &e ) {
        std::cerr << e.what() << std::endl;
    }




    m_shaderProgram2.use();
    m_shaderProgram2.setUniform("Color", glm::vec4(0.5f,1.0f,1.0f,1.0f));
}

void Entity::BezierCurve::setupGeometry()
{
    qDebug() << "/////////////////// Bez Curve Setup Geo ////////////////////";

    float c = 3.5f;
    projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f *c , 0.3f*c, 0.1f, 100.0f);
    glPointSize(10.0f);

    glEnable(GL_DEPTH_TEST);
    glGenBuffers(1, &m_vbo);

    // Set up patch VBO
    float v[] = { -1.0f, -1.0f, -0.5f, 1.0f, 0.5f, -1.0f, 1.0f, 1.0f };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), v, GL_STATIC_DRAW);

    // Set up patch VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


}

void Entity::BezierCurve::setupMatrix()
{
    qDebug() << "/////////////////// Bez Curve Setup Matrix ////////////////////";
    glm::mat4 mv = view * model;
    m_shaderProgram.use();
    m_shaderProgram.setUniform("MVP", projection * mv);
    m_shaderProgram2.use();
    m_shaderProgram2.setUniform("MVP", projection * mv);
}

void Entity::BezierCurve::update(float t)
{

}

void Entity::BezierCurve::draw()
{
    // bez curve code
    glm::vec3 cameraPos(0.0f, 0.0f, 2.5f);
    view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    model = glm::mat4(1.0f);

    glm::mat4 mv = view * model;
    qDebug() << "/////////////////// Bez Curve Draw ////////////////////";

    glBindVertexArray(m_vao);
    setupMatrix();

    m_shaderProgram.use();
    glDrawArrays(GL_PATCHES, 0, 4);
    // Draw the control points
    m_shaderProgram2.use();
    glDrawArrays(GL_POINTS, 0, 4);

    glFinish();
}
