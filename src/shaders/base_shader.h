#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <GL/glew.h>

#include "shader_set.h"

using namespace std;

class BaseShader
{
public:
    BaseShader(const std::string &vertexFilePath, const std::string &fragmentFilePath);
    ~BaseShader();
    void Use();
    void Unbind();
    void Cleanup();
    void HotReload();

protected:
    void _LoadMat4(GLint location, const GLfloat *value);
    void _LoadMat3(GLint location, const GLfloat *value);
    void _LoadBool(GLint location, bool value);
    void _LoadVec4(GLint location, glm::vec4 value);
    void _LoadVec2(GLint location, glm::vec2 value);
    void _LoadVec3(GLint location, glm::vec3 value);
    void _LoadFloat(GLint location, float value);
    void _LoadSampler2D(GLint location, GLint textureUnit);

    GLint _GetUniformLocation(string uniformName);
    void _BindAttribute(GLuint attribute, std::string variableName);
    virtual void _BindAttributes()         = 0;
    virtual void _GetAllUniformLocations() = 0;
    virtual void _CustomCleanup()          = 0;

private:
    GLuint *m_programID;
    ShaderSet m_shaderSet;
};
