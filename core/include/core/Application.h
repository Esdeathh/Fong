//
// Created by Rafik on 04.11.2018.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <core/Window.h>
#include <core/Mesh.h>
#include <core/Shader.h>
#include <core/Texture.h>
#include <common/timer.h>
#include <iostream>
#include <thread>
#include <ft2build.h>
#include <map>
#include <glm.hpp>
#include FT_FREETYPE_H

const int FPS_MAX = 60;

class Application
{
private:
    Window *m_Window;
public:
    Application(const std::string & title, int width, int height, bool fullscreen = false);
    ~Application();
private:
    bool Init(const std::string & title, int width, int height, bool fullscreen = false);
    void Run();
    void call_from_thread();
    void RenderText(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    GLuint VAO, VBO;
    struct Character {
        GLuint     TextureID;  // ID handle of the glyph texture
        glm::ivec2 Size;       // Size of glyph
        glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
        FT_Pos     Advance;    // Offset to advance to next glyph
    };

    std::map<GLchar, Character> Characters;

};

#endif //APPLICATION_H
