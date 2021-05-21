#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

const glm::vec3 BLUE = glm::vec3(0.0, 0.25, 0.5); // Darkish blue color
const glm::vec3 POINT_COLOR = glm::vec3(0.8, 0.7, 0.05); // Yellow color
const glm::vec3 LINE_COLOR = glm::vec3(0.8, 0.1, 0.0); // Red color
const GLfloat   BACKGROUND_COLOR[4] = { 0.25, 0.25, 0.25, 1.0 }; // Background color

#endif // CONSTANTS_H
