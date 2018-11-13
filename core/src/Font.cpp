//
// Created by Esdeath on 12/11/2018.
//

#include <core/Font.h>

Font::Font(std::string fontFile, glm::vec2 position, glm::vec3 color, std::string text, glm::mat4 projection, float scale):
    fontFile(fontFile), position(position), color(color), text(text), projection(projection), scale(scale) {

    init();
}

Font::~Font() {
    delete(m_VBO);
    delete(m_VAO);
    delete(shader);
}

void Font::init() {
    shader = new Shader("../resources/shaders/FontVertexShader.vs", "../resources/shaders/FontFragmentShader.fs");
    shader->Bind();
    shader->SetUniformMat4("projection", projection); //test it

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    FT_Face face;
    if (FT_New_Face(ft, fontFile.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    m_VAO = new VertexArray();
    m_VBO = new VertexBuffer(sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    VertexBufferLayout layout;
    layout.PushElement(4);
    m_VAO->BindVertexBuffer(*m_VBO, layout);
}

void Font::setPosition(glm::vec3 position) {
    this->position = position;
}

void Font::setColor(glm::vec3 color) {
    this->color = color;
}

void Font::setText(std::string text) {
    this->text = text;
}

void Font::setProjection(glm::mat4 projection) {
    this->projection = projection;
}

std::string Font::getText() {
    return this->text;
}

glm::vec2 Font::getPosition() {
    return this->position;
}

void Font::renderText() {
    shader->Bind();
    shader->SetUniform3f("textColor", color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    m_VAO->Bind();
    GLfloat x = position.x;

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = position.y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;

        GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        m_VBO->Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale;
    }
    m_VAO->Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
}

