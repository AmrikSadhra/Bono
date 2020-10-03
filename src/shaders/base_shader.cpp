#include "base_shader.h"

#include "../config.h"

BaseShader::BaseShader(const std::string &vertexFilePath, const std::string &fragmentFilePath)
{
    // Prepended to shaders
    m_shaderSet.SetVersion(BONO_GL_VERSION);

    m_programID = m_shaderSet.AddProgramFromExts({vertexFilePath, fragmentFilePath});
    m_shaderSet.UpdatePrograms();
}

void BaseShader::_LoadSampler2D(GLint location, GLint textureUnit)
{
    glUniform1i(location, textureUnit);
}

void BaseShader::_LoadBool(GLint location, bool value)
{
    glUniform1i(location, value);
}

void BaseShader::_LoadFloat(GLint location, float value)
{
    glUniform1f(location, value);
}

void BaseShader::_LoadVec4(GLint location, glm::vec4 value)
{
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void BaseShader::_LoadVec3(GLint location, glm::vec3 value)
{
    glUniform3f(location, value.x, value.y, value.z);
}

void BaseShader::_LoadVec2(GLint location, glm::vec2 value)
{
    glUniform2f(location, value.x, value.y);
}

void BaseShader::_LoadMat4(GLint location, const GLfloat *value)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void BaseShader::_LoadMat3(GLint location, const GLfloat *value)
{
    glUniformMatrix3fv(location, 1, GL_FALSE, value);
}

void BaseShader::Cleanup()
{
    _CustomCleanup();
}

void BaseShader::Use()
{
    glUseProgram(*m_programID);
}

void BaseShader::Unbind()
{
    glUseProgram(0);
}

void BaseShader::HotReload()
{
    m_shaderSet.UpdatePrograms();
}

BaseShader::~BaseShader()
{
    glDeleteProgram(*m_programID);
}

GLint BaseShader::_GetUniformLocation(std::string uniformName)
{
    return glGetUniformLocation(*m_programID, uniformName.c_str());
}

void BaseShader::_BindAttribute(GLuint attribute, std::string variableName)
{
    glBindAttribLocation(*m_programID, attribute, variableName.c_str());
}