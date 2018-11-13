//
// Created by Rafik on 04.11.2018.
//

#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader
{
private:
    unsigned int m_ID;
    std::unordered_map<std::string, int> uniforms;
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    std::string LoadShader(const std::string& path);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    void SetUniform1f(const std::string& name, float x);
    void SetUniform3f(const std::string &name, float x, float y, float z);
    void SetUniform4f(const std::string& name, float x, float y, float z, float w);
    void SetUniformMat4(const std::string& name, glm::mat4 mat);
    void SetUniform1i(const std::string& name, int i);

    int GetUniformLocation(const std::string& name);
    inline unsigned int GetID() const { return m_ID; };
};


#endif //SHADER_H
