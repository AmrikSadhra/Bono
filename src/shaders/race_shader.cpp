#include "race_shader.h"

const std::string vertexSrc = "../src/shaders/racers.vert";
const std::string fragSrc   = "../src/shaders/racers.frag";

RaceShader::RaceShader() : BaseShader(vertexSrc, fragSrc)
{
    this->_BindAttributes();
    this->_GetAllUniformLocations();
}

void RaceShader::_BindAttributes()
{
    this->_BindAttribute(0, "vertexPosition_modelspace");
}

void RaceShader::_GetAllUniformLocations()
{
    // Get handles for uniforms
    m_transformationMatrixLocation = this->_GetUniformLocation("transformationMatrix");
    m_projectionMatrixLocation     = this->_GetUniformLocation("projectionMatrix");
    m_colourLocation               = this->_GetUniformLocation("spriteColour");
}

void RaceShader::LoadProjectionMatrix(const glm::mat4 &projection)
{
    this->_LoadMat4(m_projectionMatrixLocation, &projection[0][0]);
}

void RaceShader::LoadTransformationMatrix(const glm::mat4 &transformation)
{
    this->_LoadMat4(m_transformationMatrixLocation, &transformation[0][0]);
}

void RaceShader::LoadColor(glm::vec3 color)
{
    this->_LoadVec3(m_colourLocation, color);
}

void RaceShader::_CustomCleanup()
{
}
