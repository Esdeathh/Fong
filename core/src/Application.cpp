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

void Application::fpsUpdate(Font *font, Timer *timer) {
    while(!m_Window->Closed()) {
        std::ostringstream strs;
        strs << timer->getFps();
        std::string str = strs.str();
        font->setText(str.substr(0, str.find_first_of('.') + 2));
        std::this_thread::sleep_for(1s);
    }
}

void Application::Run()
{
    Timer *mainTimer = new Timer;
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

    Shader textureShader("../resources/shaders/BasicVertexShader.vs", "../resources/shaders/BasicFragmentShader.fs");
    textureShader.SetUniform1f("texture1", 0);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));
    Font *fps = new Font("../resources/fonts/arial.ttf", glm::vec2(25.0f, 25.0f), glm::vec3(1.0f, 0.0f, 0.0f), "DUPA", projection, 1.0f);


    std::thread thread(&Application::call_from_thread, this);
    mainTimer->getElapsedTime();
    std::thread thread2(&Application::fpsUpdate, this, fps, mainTimer);
    while(!m_Window->Closed())
    {
        mainTimer->getElapsedTime();

        m_Window->Clear();
        textureShader.Bind();
        testMesh.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        fps->renderText();

        m_Window->Render();
    }
    delete(fps);
    delete(mainTimer);
    thread.join();
    thread2.join();
}


