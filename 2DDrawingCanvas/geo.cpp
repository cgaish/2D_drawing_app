#include "geo.h"

Entity::Geo::Geo()
{

}

//////////////////////////////////////// POINT GEO DEFINITIONS START /////////////////////////////////

Entity::Geo::Point::Point()
{
    qDebug() << "/////////////// IN POINT ///////////////////////////";
    // To draw points this must be initialized
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_BLEND);

}

Entity::Geo::Point::~Point()
{

}

void Entity::Geo::Point::setupShaders()
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
    //point1.setupMatrix("position", glm::vec3(0.0, 0.0, 0.0));
    //m_shaderProgram.setUniform("l_VertexPosition", glm::vec3(0.0, 0.0, 0.0));
    m_shaderProgramHandle = m_shaderProgram.getHandle();
}

void Entity::Geo::Point::setupGeometry()
{

    // temp
//    glm::vec4 ptSize = {10.0f, 2.0f, 50.0f, 99.0f};
    // temp
    qDebug() << "/////////////////// Setting Up Point Geometry ////////////////////";
    qDebug() << "Size of point position vector: " << m_pointPosition.size();
    qDebug() << "Size of point color vector: " << m_pointColor.size();
//    qDebug() << "Size of point size vector: " << m_pointSize.size() << m_pointSize[0] << m_pointSize[1] << m_pointSize[2] << m_pointSize[3];
//    qDebug() << "Size of point floats * 12: " << sizeof(glm::vec3);
    static const GLfloat v[] = {0.0, 0.0, 0.0};
    GLuint offset = 0;

    glGenVertexArrays( 1, &m_vao );
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(v) + (sizeof(glm::vec3)*m_pointColor.size()) + (sizeof(glm::vec3)*m_pointPosition.size()), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(v), v);
    offset += sizeof(v);

    glBufferSubData(GL_ARRAY_BUFFER, offset, (sizeof(glm::vec3)*m_pointColor.size()), m_pointColor.data());
    offset += (sizeof(glm::vec3)*m_pointColor.size());

    glBufferSubData(GL_ARRAY_BUFFER, offset, (sizeof(glm::vec3)*m_pointPosition.size()), m_pointPosition.data());
    offset += (sizeof(glm::vec3)*m_pointPosition.size());

//    glBufferSubData(GL_ARRAY_BUFFER, offset, (sizeof(glm::vec4)), &ptSize);
//    offset += (sizeof(glm::vec4));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)sizeof(v));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)( sizeof(v) + (sizeof(glm::vec3)*m_pointColor.size())));
//    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)( sizeof(v) + (sizeof(glm::vec3)*m_pointColor.size()) +
//                                                                   (sizeof(glm::vec3)*m_pointPosition.size())));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
//    glEnableVertexAttribArray(3);

    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
//    glVertexAttribDivisor(3, 1);
}

void Entity::Geo::Point::setupMatrix(const char *name, const glm::mat4 &m)
{
    m_shaderProgram.setUniform(name, m);
}

void Entity::Geo::Point::update()
{
    m_shaderProgram.use();
}

void Entity::Geo::Point::setPointCoord(glm::vec3 coord)
{
    m_pointPosition.push_back(coord);
    m_pointCount++;

}

void Entity::Geo::Point::setPointColor(glm::vec3 color)
{
    m_pointColor.push_back(color);
}

void Entity::Geo::Point::setPointSize(int size)
{
    m_pointSize.push_back(size);
}

int Entity::Geo::Point::getPointCount() { return m_pointCount; }

int Entity::Geo::Point::getPointShaderID() {
    m_shaderProgramHandle = m_shaderProgram.getHandle();
    return m_shaderProgramHandle;
}

void Entity::Geo::Point::draw()
{

    glUseProgram(m_shaderProgramHandle);
    glBindVertexArray(m_vao);
    glDrawArraysInstanced(GL_POINTS, 0, 1, 4 );
    glBindVertexArray(0);

}

//////////////////////////////////////// POINT GEO DEFINITIONS END /////////////////////////////////

//////////////////////////////////////// CUBIC CURVE GEO DEFINITIONS START /////////////////////////////////

Entity::Geo::CubicCurve::CubicCurve()
{
    qDebug() << "/////////////// IN CUBIC CURVE ///////////////////////////";
    // Set the number of vertices per patch.  IMPORTANT!!
    glPatchParameteri( GL_PATCH_VERTICES, 4);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_MULTISAMPLE);

}

Entity::Geo::CubicCurve::~CubicCurve()
{

}

void Entity::Geo::CubicCurve::setupShaders()
{
    qDebug() << "/////////////// IN CUBIC CURVE SETUP SHADERS ///////////////////////////";
    m_lineShaderProgram.compileShaderFromFile("../2DDrawingCanvas/bez.vs", GLShader::ShaderType::VERTEX);
    m_lineShaderProgram.compileShaderFromFile("../2DDrawingCanvas/bez.fs", GLShader::ShaderType::FRAGMENT);
    m_lineShaderProgram.compileShaderFromFile("../2DDrawingCanvas/qbez.tes", GLShader::ShaderType::TESS_EVALUATION);
    m_lineShaderProgram.compileShaderFromFile("../2DDrawingCanvas/bez.tcs", GLShader::ShaderType::TESS_CONTROL);
    m_lineShaderProgram.compileShaderFromFile("../2DDrawingCanvas/bez.gs", GLShader::ShaderType::GEOMETRY);
    bool isSuccess = false;
    isSuccess = m_lineShaderProgram.link();
    if(isSuccess) qDebug() << "line shader program linked";

    isSuccess = m_lineShaderProgram.validate();
    if(isSuccess) qDebug() << "line shader program validated";

    m_lineShaderProgram.use();
    // Assign Uniform
    qDebug() << "line shader program handle: " << m_lineShaderProgram.getHandle();
    m_lineShaderProgram.setUniform("NumSegments", 64);
    m_lineShaderProgram.setUniform("NumStrips", 8);
//    m_lineShaderProgram.setUniform("uLineWidth", 2);
//    m_lineShaderProgram.setUniform("uBlendFactor", 1.5f);
    m_lineShaderProgram.setUniform("LineColor", glm::vec4(0.5f, 1.0f, 1.0f, 1.0f));


    m_pointShaderProgram.compileShaderFromFile("../2DDrawingCanvas/cps.vs", GLShader::ShaderType::VERTEX);
    m_pointShaderProgram.compileShaderFromFile("../2DDrawingCanvas/cps.fs", GLShader::ShaderType::FRAGMENT);
    //isSuccess = false;
    isSuccess = m_pointShaderProgram.link();
    if(isSuccess) qDebug() << "point shader program linked";

    isSuccess = m_pointShaderProgram.validate();
    if(isSuccess) qDebug() << "point shader program validated";
    m_pointShaderProgram.link();
    m_pointShaderProgram.validate();
    m_pointShaderProgram.use();
    m_pointShaderProgram.setUniform("Color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    qDebug() << "point shader program handle: " << m_pointShaderProgram.getHandle();
}

void Entity::Geo::CubicCurve::setupGeometry()
{
    qDebug() << "/////////////// IN CUBIC CURVE SETUP GEOMETRY ///////////////////////////";
    glPointSize(10.0f);

    // Set up patch VBO
//    float v[] = {-1.0f, -1.0f, -0.5f, 1.0f, 0.5f, -1.0f, 1.0f, 1.0f};
    float v[] = {-0.5, -0.2f, 0.0f, 0.5f, 0.5f, -0.2f};

    glGenBuffers(1, m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), v, GL_STATIC_DRAW);

    // Set up patch VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Entity::Geo::CubicCurve::setupMatrix()
{
    qDebug() << "/////////////// IN CUBIC CURVE SETUP MATRIX ///////////////////////////";
    float c = 3.0f;
    glm::vec3 cameraPos(0.0f ,0.0f,1.5f);
    view = glm::lookAt(cameraPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));

    model = glm::mat4(1.0f);
    projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f *c, 0.3f*c, 0.1f,50.0f);
    glm::mat4 mv = view * model;
    m_lineShaderProgram.use();
    m_lineShaderProgram.setUniform("MVP", projection * mv);
    m_pointShaderProgram.use();
    m_pointShaderProgram.setUniform("MVP", projection * mv);
}

void Entity::Geo::CubicCurve::update()
{
    setupGeometry();
}

void Entity::Geo::CubicCurve::draw()
{
    qDebug() << "/////////////// IN CUBIC CURVE DRAW ///////////////////////////";
    glBindVertexArray(m_vao);
    setupMatrix();

    // Draw the control points
    m_pointShaderProgram.use();
    glDrawArrays(GL_POINTS, 0, 3);
    // Draw the curve
//    glPatchParameteri(GL_PATCH_VERTICES, 3);
    m_lineShaderProgram.use();
    glDrawArrays(GL_PATCHES, 0, 124);


    glFinish();
}

//////////////////////////////////////// CUBIC CURVE GEO DEFINITIONS ENDS /////////////////////////////////

Entity::Geo::Quad::Quad()
{
    // Set the number of vertices per patch.  IMPORTANT!!
    glPatchParameteri( GL_PATCH_VERTICES, 4);
}

Entity::Geo::Quad::~Quad()
{
    
}

void Entity::Geo::Quad::setupShaders()
{
    qDebug() << "/////////////// IN QUAD SETUP SHADERS ///////////////////////////";
    m_quadShaderProgram.compileShaderFromFile("../2DDrawingCanvas/quad.vs", GLShader::ShaderType::VERTEX);
    m_quadShaderProgram.compileShaderFromFile("../2DDrawingCanvas/quad.fs", GLShader::ShaderType::FRAGMENT);
    m_quadShaderProgram.compileShaderFromFile("../2DDrawingCanvas/quad.gs", GLShader::ShaderType::GEOMETRY);
    m_quadShaderProgram.compileShaderFromFile("../2DDrawingCanvas/quad.tes", GLShader::ShaderType::TESS_EVALUATION);
    m_quadShaderProgram.compileShaderFromFile("../2DDrawingCanvas/quad.tcs", GLShader::ShaderType::TESS_CONTROL);
    bool isSuccess = false;
    isSuccess = m_quadShaderProgram.link();
    isSuccess ? qDebug() << "quad shader program linked" :
                qDebug() << "quad shader program not linked";

    isSuccess = m_quadShaderProgram.validate();
    isSuccess ? qDebug() << "quad shader program validated" :
                qDebug() << "quad shader program not validated";

    m_quadShaderProgram.use();
    qDebug() << "quad shader program handle: " << m_quadShaderProgram.getHandle();

    // Assign Uniform
    ///////////// Uniforms ////////////////////
    m_quadShaderProgram.setUniform("Inner", 4);
    m_quadShaderProgram.setUniform("Outer", 4);
    m_quadShaderProgram.setUniform("LineWidth", 0.1f);
    m_quadShaderProgram.setUniform("LineColor", glm::vec4(0.05f,0.0f,0.05f,1.0f));
    m_quadShaderProgram.setUniform("QuadColor", glm::vec4(1.0f,1.0f,1.0f,1.0f));

}

void Entity::Geo::Quad::setupGeometry()
{
    qDebug() << "/////////////// IN QUAD SETUP GEOMETRY ///////////////////////////";


    glClearColor(0.5f,0.5f,0.5f,1.0f);

    glEnable(GL_DEPTH_TEST);

    float c = 3.5f;
    projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f *c, 0.3f*c, 0.1f, 100.0f);

    // Set up patch VBO
    float v[] = {-1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f};

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), v, GL_STATIC_DRAW);
    qDebug() << "quad vbo handle binded";

    // Set up patch VAO
    glGenVertexArrays( 1, &m_vao );
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    qDebug() << "quad attrib pointer set";

    glBindVertexArray(0);

    GLint maxVerts;
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxVerts);
    qDebug() << "quad max verts: " << maxVerts;
}

void Entity::Geo::Quad::setupMatrix()
{
    qDebug() << "/////////////// IN QUAD SETUP MATRIX ///////////////////////////";
    glm::mat4 mv = view * model;
    m_quadShaderProgram.setUniform("MVP", projection * mv);
    m_quadShaderProgram.setUniform("ViewportMatrix", view);
    qDebug() << "setup matrix done";
}

void Entity::Geo::Quad::update()
{
    
}

void Entity::Geo::Quad::draw()
{
    qDebug() << "/////////////// IN QUAD DRAW ///////////////////////////";


    glm::vec3 cameraPos(0.0f,0.0f,1.5f);
    view = glm::lookAt(cameraPos,
                       glm::vec3(0.0f,0.0f,0.0f),
                       glm::vec3(0.0f,1.0f,0.0f));

    model = glm::mat4(1.0f);
    setupMatrix();

    qDebug() << "quad begin drawing";
    m_quadShaderProgram.use();
    glBindVertexArray(m_vao);
    qDebug() << "vao bind success";
    glDrawArrays(GL_PATCHES, 0, 4);

    glFinish();
}

//////////////////////////////////////// TRIANGLES GEO DEFINITIONS ENDS /////////////////////////////////

Entity::Geo::Triangles::Triangles()
{

}

Entity::Geo::Triangles::~Triangles()
{

}

void Entity::Geo::Triangles::setupShaders()
{
    qDebug() << "/////////////// IN QUAD SETUP SHADERS ///////////////////////////";
    m_quadShaderProgram.compileShaderFromFile("../2DDrawingCanvas/triangle.vert", GLShader::ShaderType::VERTEX);
    m_quadShaderProgram.compileShaderFromFile("../2DDrawingCanvas/triangle.frag", GLShader::ShaderType::FRAGMENT);
    bool isSuccess = false;
    isSuccess = m_quadShaderProgram.link();
    isSuccess ? qDebug() << "triangle shader program linked" :
                qDebug() << "triangle shader program not linked";

    isSuccess = m_quadShaderProgram.validate();
    isSuccess ? qDebug() << "triangle shader program validated" :
                qDebug() << "triangle shader program not validated";

    m_quadShaderProgram.use();
    qDebug() << "triangle shader program handle: " << m_quadShaderProgram.getHandle();
}

void Entity::Geo::Triangles::setupGeometry()
{
    GLfloat  v[6][2] = {
           { -0.90f, -0.90f }, {  0.85f, -0.90f }, { -0.90f,  0.85f },  // Triangle 1
           {  0.90f, -0.85f }, {  0.90f,  0.90f }, { -0.85f,  0.90f }   // Triangle 2
       };

    // Set up triangle VAO
    glGenVertexArrays( 1, &m_vao );
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), v, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(0));
    glEnableVertexAttribArray(0);
}

void Entity::Geo::Triangles::setupMatrix()
{

}

void Entity::Geo::Triangles::update()
{

}

void Entity::Geo::Triangles::draw()
{
    glBindVertexArray( m_vao );
    glDrawArrays( GL_TRIANGLES, 0, 6 );
}

//////////////////////////////////////// PARTICLES GEO DEFINITIONS ENDS /////////////////////////////////

Entity::Geo::Particles::Particles():
    time(0), particleLifetime(5.5f), emitterPos(1,0,0), nParticles(8000),  emitterDir(-1,2,0)
{
    glClearColor(0.1f,0.1f,0.1f,1.0f);
    //angle= 0;
    angle = glm::half_pi<float>();
    resize(1200, 720);
    setupShaders();
    setupGeometry();
}

Entity::Geo::Particles::~Particles()
{
    
}

void Entity::Geo::Particles::setupShaders()
{
    // The particle texture
    glActiveTexture(GL_TEXTURE0);
    Texture::loadTexture("../2DDrawingCanvas/bluewater.png");

    qDebug() << "/////////////// IN PARTICLE SETUP SHADERS ///////////////////////////";
    renderProg.compileShaderFromFile("../2DDrawingCanvas/particles.vs", GLShader::ShaderType::VERTEX);
    renderProg.compileShaderFromFile("../2DDrawingCanvas/particles.fs", GLShader::ShaderType::FRAGMENT);
    bool isSuccess = false;
    isSuccess = renderProg.link();
    isSuccess ? qDebug() << "particle shader program linked" :
                qDebug() << "particle shader program not linked";

    isSuccess = renderProg.validate();
    isSuccess ? qDebug() << "particle shader program validated" :
                qDebug() << "particle shader program not validated";

    renderProg.use();
    renderProg.setUniform("ParticleTex", 0);
    renderProg.setUniform("ParticleLifetime", particleLifetime);
    renderProg.setUniform("ParticleSize", 0.05f);
    renderProg.setUniform("Gravity", glm::vec3(0.0f,-0.2f,0.0f));
    renderProg.setUniform("EmitterPos", emitterPos);
    qDebug() << "particle shader program handle: " << renderProg.getHandle();


    flatProg.compileShaderFromFile("../2DDrawingCanvas/flat.vs", GLShader::ShaderType::VERTEX);
    flatProg.compileShaderFromFile("../2DDrawingCanvas/flat.fs", GLShader::ShaderType::FRAGMENT);

    isSuccess = flatProg.link();
    isSuccess ? qDebug() << "flat shader program linked" :
                qDebug() << "flat shader program not linked";

    isSuccess = flatProg.validate();
    isSuccess ? qDebug() << "flat shader program validated" :
                qDebug() << "flat shader program not validated";

    flatProg.use();
    flatProg.setUniform("Color", glm::vec4(0.4f,0.4f,0.4f,1.0f));

}

void Entity::Geo::Particles::setupGeometry()
{
    // Allocate space for all buffers
    int size = nParticles * sizeof(float);
    // Fill the first velocity buffer with random velocities
    glm::mat3 emitterBasis = ParticleUtils::makeArbitraryBasis(emitterDir);
    glm::vec3 v(0.0f);
    float velocity, theta, phi;
    std::vector<GLfloat> data(nParticles * 3);
    for (uint32_t i = 0; i < nParticles; i++ ) {

        theta = glm::mix(0.0f, glm::pi<float>() / 20.0f, randFloat());
        phi = glm::mix(0.0f, glm::two_pi<float>(), randFloat());

        v.x = sinf(theta) * cosf(phi);
        v.y = cosf(theta);
        v.z = sinf(theta) * sinf(phi);

        velocity = glm::mix(1.25f,1.5f,randFloat());
        v = glm::normalize(emitterBasis * v) * velocity;

        data[3*i]   = v.x;
        data[3*i+1] = v.y;
        data[3*i+2] = v.z;
    }

    // Fill the start time buffer
    float rate = particleLifetime / nParticles;
    for( int i = 0; i < nParticles; i++ ) {
        data[i] = rate * i;
    }

    // Generate the buffers for initial velocity and start (birth) time
    glGenBuffers(1, &initVel);   // Initial velocity buffer
    glGenBuffers(1, &startTime); // Start time buffer

    glBindBuffer(GL_ARRAY_BUFFER, initVel);
    glBufferData(GL_ARRAY_BUFFER, size * 3, 0, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, startTime);
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER,initVel);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size * 3, data.data());


    glBindBuffer(GL_ARRAY_BUFFER,startTime);
    glBufferSubData(GL_ARRAY_BUFFER, 0, nParticles * sizeof(float), data.data());

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glGenVertexArrays(1, &particles);
    glBindVertexArray(particles);
    glBindBuffer(GL_ARRAY_BUFFER, initVel);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, startTime);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glVertexAttribDivisor(0,1);
    glVertexAttribDivisor(1,1);

    glBindVertexArray(0);

}

void Entity::Geo::Particles::setMatrices(GLShaderProgram &p)
{
    glm::mat4 mv = view * model;
    p.setUniform("MV", mv);
    p.setUniform("Proj", projection);
}

void Entity::Geo::Particles::update(float t)
{
    time = t;
    angle = std::fmod(angle + 0.01f, glm::two_pi<float>());
}

void Entity::Geo::Particles::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    view = glm::lookAt(glm::vec3(3.0f * cos(angle),1.5f,3.0f * sin(angle)), glm::vec3(0.0f,1.5f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    model = glm::mat4(1.0f);

    flatProg.use();
    setMatrices(flatProg);
    grid.render();    
    renderProg.use();
    setMatrices(renderProg);
    renderProg.setUniform("Time", time);
    update(time);
    glDepthMask(GL_FALSE);
    glBindVertexArray(particles);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, nParticles);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}

float Entity::Geo::Particles::randFloat()
{
    return rand.nextFloat();
}

void Entity::Geo::Particles::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(60.0f), (float)w/h, 0.3f, 100.0f);
}


Entity::Geo::Circle::Circle()
{
    glEnable(GL_MULTISAMPLE);
}

Entity::Geo::Circle::~Circle()
{

}

void Entity::Geo::Circle::setupShaders()
{
    renderProg.compileShaderFromFile("../2DDrawingCanvas/circle.vs", GLShader::ShaderType::VERTEX);
    renderProg.compileShaderFromFile("../2DDrawingCanvas/circle.gs", GLShader::ShaderType::GEOMETRY);
    renderProg.compileShaderFromFile("../2DDrawingCanvas/circle.fs", GLShader::ShaderType::FRAGMENT);
    bool isSuccess = false;
    isSuccess = renderProg.link();
    isSuccess ? qDebug() << "circle shader program linked" :
                qDebug() << "circle shader program not linked";

    isSuccess = renderProg.validate();
    isSuccess ? qDebug() << "circle shader program validated" :
                qDebug() << "circle shader program not validated";

    renderProg.use();
    qDebug() << "circle shader program handle: " << renderProg.getHandle();

}

void Entity::Geo::Circle::setupGeometry()
{
    float points[] = {
           0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  48.0f,
//         0.45f,  0.45f, 0.0f, 1.0f, 0.0f,  8.0f,
//         0.45f, -0.45f, 0.0f, 0.0f, 1.0f, 16.0f,
//        -0.45f, -0.45f, 1.0f, 1.0f, 0.0f, 32.0f
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof (points), points, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLint attribVPos = glGetAttribLocation(renderProg.getHandle(), "VertexPosition");
    glEnableVertexAttribArray(attribVPos);
    glVertexAttribPointer(attribVPos, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    GLint attribVCol = glGetAttribLocation(renderProg.getHandle(), "VertexColor");
    glEnableVertexAttribArray(attribVCol);
    glVertexAttribPointer(attribVCol, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (2 * sizeof(float)));

    GLint attribCSides = glGetAttribLocation(renderProg.getHandle(), "CircleSides");
    glEnableVertexAttribArray(attribCSides);
    glVertexAttribPointer(attribCSides, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (5 * sizeof(float)));

}

void Entity::Geo::Circle::draw()
{
    glPointSize(5.0f);
    glLineWidth(10.0f);
    renderProg.use();

    glDrawArrays(GL_LINES, 0, 4);
}



/////////////////////////////////////////////////// Curve //////////////////////////////////////////////////////////

Entity::Geo::Curve::Curve()
{
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
}

Entity::Geo::Curve::~Curve()
{

}

void Entity::Geo::Curve::setupShaders()
{

    try {
        m_pointShaderProgram.compileShaderFromFile("../2DDrawingCanvas/point.vert",
                                                 GLShader::ShaderType::VERTEX );
        m_pointShaderProgram.compileShaderFromFile("../2DDrawingCanvas/point.frag",
                                                 GLShader::ShaderType::FRAGMENT);

        m_pointShaderProgram.link();
        m_pointShaderProgram.validate();
        m_pointShaderProgram.use();

    }  catch ( GLShaderException &e ) {
        std::cerr << e.what() << std::endl;
    }
    //point1.setupMatrix("position", glm::vec3(0.0, 0.0, 0.0));
    //m_shaderProgram.setUniform("l_VertexPosition", glm::vec3(0.0, 0.0, 0.0));
    m_pointShaderProgramHandle = m_pointShaderProgram.getHandle();

    m_lineShaderProgram.compileShaderFromFile("../2DDrawingCanvas/Curve.vs", GLShader::ShaderType::VERTEX);
//    renderProg.compileShaderFromFile("../2DDrawingCanvas/Curve.gs", GLShader::ShaderType::GEOMETRY);
    m_lineShaderProgram.compileShaderFromFile("../2DDrawingCanvas/Curve.fs", GLShader::ShaderType::FRAGMENT);
    bool isSuccess = false;
    isSuccess = m_lineShaderProgram.link();
    isSuccess ? qDebug() << "Curve shader program linked" :
                qDebug() << "Curve shader program not linked";

    isSuccess = m_lineShaderProgram.validate();
    isSuccess ? qDebug() << "Curve shader program validated" :
                qDebug() << "Curve shader program not validated";

    m_lineShaderProgram.use();
    m_lineShaderProgramHandle = m_lineShaderProgram.getHandle();
    qDebug() << "Curve shader program handle: " << m_lineShaderProgram.getHandle();
}

void Entity::Geo::Curve::setupGeometry()
{
    float v[] = {-0.5, -0.2f, 0.0f, 0.5f, 0.5f, -0.2f};
//    float v[] = {   // positions    // weights
//                    217.63, 136.36, //48.00 ,48.00,
//                    55.10 , 117.40, //48.00 ,48.00,
//                    109.28, 185.12, //48.00 ,48.00,
//                    279.93, 269.10, //48.00 ,48.00,
//                    942.58, 668.99, //48.00 ,48.00,
//                    387.27, 408.94, //48.00 ,48.00,
//                    184.11, 547.09, //48.00 ,48.00,
//                    609.39, 801.72, //48.00 ,48.00,
//                };
    // Send control points to calculate interpolated points
    int sizeOfArray = (sizeof (v)/sizeof(v[0]));
    quadCurve = getQuadraticCurve(v, sizeOfArray);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(v), v, GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    GLint posAttrib = glGetAttribLocation(m_pointShaderProgramHandle, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);


    /// Curve Buffers
    glGenBuffers(1, &m_vbo_curve);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_curve);
    glBufferData(GL_ARRAY_BUFFER, quadCurve.size()*sizeof (float), quadCurve.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao_curve);
    glBindVertexArray(m_vao_curve);

    GLint curvePosAttrib = glGetAttribLocation(m_lineShaderProgramHandle, "VertexPosition");
    glEnableVertexAttribArray(curvePosAttrib);
    glVertexAttribPointer(curvePosAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void Entity::Geo::Curve::setMatrices(GLShaderProgram &p)
{
    Q_UNUSED(p);
}

void Entity::Geo::Curve::update(float t)
{
    Q_UNUSED(t);
}

void Entity::Geo::Curve::draw()
{
    glBindVertexArray(m_vao);
    m_pointShaderProgram.use();
    glDrawArrays(GL_POINTS, 0, 3);
    glBindVertexArray(m_vao_curve);
    m_lineShaderProgram.use();
    glDrawArrays(GL_LINE_STRIP, 0, quadCurve.size()/2);
}

float Entity::Geo::Curve::randFloat()
{
    return 0;
}

void Entity::Geo::Curve::resize(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

std::vector<float> Entity::Geo::Curve::getQuadraticCurve(float *a, int sizeOfArray)
{
    std::vector<float> interpolatedCurvePoints = {};

    glm::vec2 p0 = {a[0], a[1]};//{0.0, 0.0};
    glm::vec2 p1 = {a[2], a[3]};//{0.0, 0.0};
    glm::vec2 p2 = {a[4], a[5]};//{0.0, 0.0};
    qDebug() << "Size Of Array: " << sizeOfArray;
//    for (int i = 0; i < sizeOfArray-2; i++){

//        if(i == 0)
//        {
//            glm::vec2 p0 = {a[i], a[i+1]};
//            glm::vec2 p1 = {a[i+2], a[i+3]};
//            glm::vec2 p2 = {a[i+4], a[i+5]};
//        }
//        else if(i == 2){
//            glm::vec2 p0 = {a[i-2], a[i-1]};
//            glm::vec2 p1 = {a[i], a[i+1]};
//            glm::vec2 p2 = {a[i+2], a[i+3]};
//        }

        float t = 0.0;
        while(t <= 1.05){
        float one_minus_t = (1.0 - t);
        float one_minus_t_square = one_minus_t * one_minus_t;
        float t_square = t * t;
        float two_times_one_minus_t = 2 * one_minus_t;
        float w1 = 1.0; float w3 = 1.0;
        float w2 =  48;

    //    glm::vec2 p = one_minus_t_square * p0 + two_times_one_minus_t*t*p1 + t_square * p2 ;
        glm::vec2 p = (( p0*w1*one_minus_t_square) + ((p1*w2)*(two_times_one_minus_t*t)) + (p2*w3*t_square) ) / ((w1*one_minus_t_square) + (w2*two_times_one_minus_t*t) + (w3*t_square));
        interpolatedCurvePoints.push_back(p.x);
        interpolatedCurvePoints.push_back(p.y);
        t += 0.05;
        }
        for(int i = 0; i < interpolatedCurvePoints.size(); i++){
            qDebug() << "X: " << interpolatedCurvePoints[i];
            qDebug() << "Y: " << interpolatedCurvePoints[i+1];
        }

        return interpolatedCurvePoints;

//    }
}
