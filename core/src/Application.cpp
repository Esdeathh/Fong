//
// Created by Rafik on 04.11.2018.
//

#include <Application.h>

Application::Application(const std::string & title, int width, int height, bool fullscreen)
{
    Init(title, width, height, fullscreen);
    Run();
}

Application::~Application()
{
    delete m_Window;
    m_Window = nullptr;
}

bool Application::Init(const std::string & title, int width, int height, bool fullscreen)
{
    m_Window = new Window(title, width, height, fullscreen);

    return false;
}

void Application::Run()
{
    float vertices[] = {
            0.5f,  0.5f, 0.0f, // Prawy górny
            0.5f, -0.5f, 0.0f, // Prawy dolny
           -0.5f, -0.5f, 0.0f, // Lewy dolny
           -0.5f,  0.5f, 0.0f  // Lewy górny
    };

    unsigned int indices[] = {
            0, 1, 3,  // Pierwszy trójkąt
            1, 2, 3 // Drugi trójkąt
    };

    VertexArray VAO;
    VertexBuffer VBO(4 * 3 * sizeof(float), vertices);
    VertexBufferLayout layout;
    layout.PushElement(3);
    IndexBuffer IBO(6, indices);

    VAO.BindVertexBuffer(VBO, layout);
    VAO.BindIndexBuffer(IBO);

    Shader shader("../resources/shaders/BasicVertexShader.vs", "../resources/shaders/BasicFragmentShader.fs");

    float red = 0.0f;
    float c = 0.005f;
    while(!m_Window->Closed())
    {
        if(red > 1)
            c = -c;
        else if(red < 0)
            c = -c;

        red += c;

        m_Window->Clear();
        shader.Bind();
        shader.SetUniform4f("ourColor", red, 0.5f, 0.3f, 1.0f);
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        m_Window->Update();
    }
}
