//
// Created by Rafik on 04.11.2018.
//

#include <core/Application.h>
#include <core/Rectangle.h>
#include <core/Circle.h>
#include <glm/glm.hpp>

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

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));

    Font *fps = new Font("../resources/fonts/arial.ttf", glm::vec2(25.0f, 25.0f), glm::vec3(1.0f, 0.0f, 0.0f), "DUPA", projection, 1.0f);

    Shader tilesShader("../resources/shaders/ColorRect.vs", "../resources/shaders/ColorRect.fs");
    tilesShader.Bind();
    tilesShader.SetUniformMat4("projection", projection);

    std::vector<core::Rectangle *> tiles;
    for(int i = 50; i < 550; i += 10) {
        for(int j = 10; j < 800; j += 10)
            tiles.push_back(new core::Rectangle(glm::vec3(j, i, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec2(0.0f, 0.0f), true, glm::vec2(4.7f, 4.7f)));
    }

    glClearColor(0.2f, 0.1f, 0.05f, 1.0f);


    Shader circleShader("../resources/shaders/CircleVertexShader.vs", "../resources/shaders/CircleFragmentShader.fs");
    circleShader.Bind();
    circleShader.SetUniformMat4("projection", projection);

    core::Circle circ(glm::vec3(400.0f, 300.0f, 0.0f), glm::vec3(0.7f, 0.3f, 0.6), glm::vec2(50.0f, 50.0f), true, 20);

    Shader playerShader("../resources/shaders/PlayerVS.vs", "../resources/shaders/Player.fs");
    playerShader.Bind();
    playerShader.SetUniformMat4("projection", projection);

    Player player1(glm::vec3(725.0f, 20.0f, 0.0f), glm::vec3(0.3f, 0.7f, 0.1f), glm::vec2(0.0f, 50.0f), true, glm::vec2(75.0f, 10.0f));
    Player player2(glm::vec3(400.0f, 580.0f, 0.0f), glm::vec3(0.3f, 0.7f, 0.1f), glm::vec2(0.0f, 50.0f), true, glm::vec2(75.0f, 10.0f));

    std::thread thread(&Application::call_from_thread, this);
    mainTimer->getElapsedTime();
    std::thread thread2(&Application::fpsUpdate, this, fps, mainTimer);
    while(!m_Window->Closed())
    {
        mainTimer->getElapsedTime();

        m_Window->Clear();

        tilesShader.Bind();
        tiles[0]->BindMesh();
        for(int i = 0; i < tiles.size(); i++)
            tiles[i]->Draw(tilesShader);

        //glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, 800 * 600);

        playerShader.Bind();
        player1.BindMesh();
        player1.Draw(tilesShader);
        player2.Draw(tilesShader);
        circleShader.Bind();
        circ.Draw(circleShader);


        fps->renderText();

        m_Window->Render();
    }
    delete(fps);
    delete(mainTimer);
    thread.join();
    thread2.join();
}


