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
    Timer mainTimer;
    Timer inputTimer;
    Timer tmpTimer;
    double timeForInput;
    double mainDelta;
    double inputDelta;
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
    int i = 0;
    while(!m_Window->Closed())
    {
        //TODO: double sub sucks....

        mainDelta = mainTimer.getElapsedTime();
        inputDelta = inputTimer.getElapsedTime();
        timeForInput = mainDelta - inputDelta;
        tmpTimer.getTime();
        do {
            timeForInput -= tmpTimer.getElapsedTime();
            i++;
            m_Window->ProcessInput();
        } while(timeForInput > 0);
        std::cout << mainTimer.getFps() << " ilosc pobran: " << i << "    " << timeForInput << "   " << mainDelta << "      " << inputTimer.getLastElapsedTime() << std::endl;
        i = 0;

        ////////////////////
        inputTimer.getTime();
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
}
