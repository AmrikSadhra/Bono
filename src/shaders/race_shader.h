#pragma once

#include "base_shader.h"

#include <glm/detail/type_mat4x4.hpp>

class RaceShader : public BaseShader
{
public:
    explicit RaceShader();
    void LoadColor(glm::vec3 color);
    void LoadProjectionMatrix(const glm::mat4 &projection);
    void LoadTransformationMatrix(const glm::mat4 &transformation);

protected:
    void _BindAttributes() override;
    void _GetAllUniformLocations() override;
    void _CustomCleanup() override;

    GLint m_transformationMatrixLocation;
    GLint m_projectionMatrixLocation;
    GLint m_colourLocation;
};
