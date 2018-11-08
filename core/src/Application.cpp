//
// Created by Rafik on 04.11.2018.
//

#include <Application.h>
#include <core/Application.h>


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

void Application::call_from_thread() {
    while(!m_Window->Closed()) {
        m_Window->ProcessInput();
        std::this_thread::sleep_for(5ms);
    }
}

void Application::Run()
{
    Timer mainTimer;
    float vertices[] = {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // Prawy górny
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Prawy dolny
           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// Lewy dolny
           -0.5f,  0.5f, 0.0f, 0.0f, 1.0f// Lewy górny
    };

    unsigned int indices[] = {
            0, 1, 3,  // Pierwszy trójkąt
            1, 2, 3 // Drugi trójkąt
    };

    VertexArray VAO;
    VertexBuffer VBO(4 * 5 * sizeof(float), vertices);
    VertexBufferLayout layout;
    layout.PushElement(3);
    layout.PushElement(2);
    IndexBuffer IBO(6, indices);

    VAO.BindVertexBuffer(VBO, layout);
    VAO.BindIndexBuffer(IBO);

    Shader shader("../resources/shaders/BasicVertexShader.vs", "../resources/shaders/BasicFragmentShader.fs");
    Texture texture("../resources/textures/awesomeface.png", true);

    shader.SetUniform1f("texture1", 0);

    float red = 0.0f;
    float c = 0.005f;
    std::thread thread(&Application::call_from_thread, this);
    while(!m_Window->Closed())
    {
        mainTimer.getElapsedTime();

        if(red > 1)
            c = -c;
        else if(red < 0)
            c = -c;

        red += c;

        m_Window->Clear();
        texture.Bind();
        shader.Bind();
        //shader.SetUniform4f("ourColor", red, 0.5f, 0.3f, 1.0f);
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        m_Window->Render();
    }
    thread.join();
}


