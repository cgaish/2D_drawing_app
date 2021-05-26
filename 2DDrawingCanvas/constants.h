#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Default Colors
const glm::vec3 BLUE = glm::vec3(0.0, 0.25, 0.5); // Darkish blue color
const glm::vec3 POINT_COLOR = glm::vec3(0.8, 0.7, 0.05); // Yellow color
const glm::vec3 LINE_COLOR = glm::vec3(0.8, 0.1, 0.0); // Red color
const GLfloat   BACKGROUND_COLOR[4] = { 0.25, 0.25, 0.25, 1.0 }; // Background color

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
const float NDC_MIN     = -1.0f; // Normalized Device Coordinates
const float NDC_MAX     =  1.0f; // Normalized Device Coordinates

// Default matrices
const glm::mat4 I_MATRIX = glm::mat4(1.0f); // Identity Matrix
const glm::vec3 XAXIS = glm::vec3(1,0,0);
const glm::vec3 YAXIS = glm::vec3(0,1,0);
const glm::vec3 ZAXIS = glm::vec3(0,0,1);
#endif // CONSTANTS_H
