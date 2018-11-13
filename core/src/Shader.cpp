//
// Created by Rafik on 04.11.2018.
//

#include <Shader.h>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <core/Shader.h>


Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    std::string sourceVS = LoadShader(vertexShaderPath);
    std::string sourceFS = LoadShader(fragmentShaderPath);

    m_ID = CreateShader(sourceVS, sourceFS);
}

Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

std::string Shader::LoadShader(const std::string& path)
{
    std::ifstream stream(path);

    std::string line;
    std::stringstream shader;
    while(std::getline(stream, line))
        shader << line << "\n";

    return shader.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        auto info = new char[length];
        glGetShaderInfoLog(shader, length, &length, info);
        std::cout << "WARNING: " << ((type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT") << "shader compilation\n" << info << std::endl;
        delete[] info;

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int VShader = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int FShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, VShader);
    glAttachShader(program, FShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        auto info = new char[length];
        glGetProgramInfoLog(program, length, &length, info);
        std::cout << "WARNING: program linking\n" << info << std::endl;
        delete[] info;

        glDeleteShader(VShader);
        glDeleteShader(FShader);
        glDeleteProgram(program);

        return 0;
    }

    glDeleteShader(VShader);
    glDeleteShader(FShader);

    return program;
}

void Shader::Bind() const
{
    glUseProgram(m_ID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1f(const std::string &name, float x)
{
    glUniform1f(GetUniformLocation(name), x);
}

void Shader::SetUniform3f(const std::string &name, float x, float y, float z)
{
    Bind();
    glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetUniform4f(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetUniformMat4(const std::string &name, glm::mat4 matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1i(const std::string &name, int i)
{
    glUniform1i(GetUniformLocation(name), i);
}

int Shader::GetUniformLocation(const std::string &name)
{
    if(uniforms.find(name) != uniforms.end())
        return uniforms.find(name)->second;

    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1)
        std::cout << "WARNING: uniform '" << name << "' doesn't exist!" << std::endl;

    uniforms.emplace(name, location);
    return location;
}


