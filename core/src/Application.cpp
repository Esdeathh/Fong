//
// Created by Rafik on 04.11.2018.
//

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
    std::vector<Vertex> vertices = {
            { glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0), glm::vec2(1.0f, 1.0f) }, // Prawy górny
            { glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0), glm::vec2(1.0f, 0.0f) }, // Prawy dolny
            { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0), glm::vec2(0.0f, 0.0f) }, // Lewy dolny
            { glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0), glm::vec2(0.0f, 1.0f) }  // Lewy górny
    };

    std::vector<unsigned int> indices = {
            0, 1, 3,  // Pierwszy trójkąt
            1, 2, 3 // Drugi trójkąt
    };

    std::vector<Texture *> textures
    {
        new Texture("../resources/textures/awesomeface.png", true)
    };

    Mesh testMesh(vertices, indices, textures);

    Shader shader("../resources/shaders/BasicVertexShader.vs", "../resources/shaders/BasicFragmentShader.fs");
    shader.SetUniform1f("texture1", 0);

    std::thread thread(&Application::call_from_thread, this);
    while(!m_Window->Closed())
    {
        mainTimer.getElapsedTime();

        m_Window->Clear();

        shader.Bind();
        testMesh.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        m_Window->Render();
    }
    thread.join();
}


