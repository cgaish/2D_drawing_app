#include "orthographiccamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix( glm::ortho(left ,right, bottom, top, NDC_MIN, NDC_MAX)), m_ViewMatrix(I_MATRIX)
{
    qDebug() << "/////////////////// Setting Up Camera ////////////////////";
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // Order matters projection * view * model
}

void OrthographicCamera::RecalculateViewMatrix()
{
    glm::mat4 transform = glm::translate(I_MATRIX, m_Position) *
                          glm::rotate(I_MATRIX, m_Rotation, ZAXIS); // model matrix

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; // Order matters projection * view * model
}
