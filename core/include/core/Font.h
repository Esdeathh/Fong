//
// Created by Esdeath on 12/11/2018.
//

#ifndef FONG_FONTRENDERER_H
#define FONG_FONTRENDERER_H

#include <core/Shader.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <map>
#include <core/VertexArray.h>


class Font {
public:
    Font(std::string fontFile, glm::vec2 position, glm::vec3 color, std::string text, glm::mat4 projection, float scale);
    ~Font();

    void renderText();

    void setPosition(glm::vec3 position);
    void setColor(glm::vec3 color);
    void setText(std::string text);
    void setProjection(glm::mat4 projection);

    std::string getText();
    glm::vec2 getPosition();

private:
    void init();

    std::string fontFile;
    glm::vec3 color;
    glm::vec2 position;
    std::string text;
    glm::mat4 projection;
    Shader *shader;
    VertexArray *m_VAO;
    VertexBuffer *m_VBO;
    float scale;

    struct Character {
        GLuint TextureID;   // ID handle of the glyph texture
        glm::ivec2 Size;    // Size of glyph
        glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
        FT_Pos Advance;    // Horizontal offset to advance to next glyph
    };
    std::map<GLchar, Character> Characters;
};


#endif //FONG_FONTRENDERER_H
