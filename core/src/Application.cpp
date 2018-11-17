//
// Created by Rafik on 04.11.2018.
//

#include <core/Application.h>
#include <core/Rectangle.h>
#include <core/Circle.h>
#include <glm/glm.hpp>

#include <common/Debug.h>

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

    Shader rectangleShader("../resources/shaders/Sprite.vs", "../resources/shaders/Sprite.fs");
    rectangleShader.Bind();
    rectangleShader.SetUniformMat4("projection", projection);
    rectangleShader.SetUniform1f("texture1", 0);

    core::Rectangle rect1(glm::vec3(200.0f, 200.0f, 0.0f), glm::vec2(50.0f, 50.0f), true, glm::vec2(50.0f, 50.0f), "../resources/textures/awesomeface.png");
    core::Rectangle rect2(glm::vec3(200.0f, 400.0f, 0.0f), glm::vec2(50.0f, 90.0f), true, glm::vec2(50.0f, 50.0f), "../resources/textures/awesomeface.png");


    Shader rectShader("../resources/shaders/ColorRect.vs", "../resources/shaders/ColorRect.fs");
    core::Rectangle rect3(glm::vec3(700.0f, 400.0f, 0.0f), glm::vec3(0.3f, 0.7f, 0.1), glm::vec2(50.0f, 90.0f), true, glm::vec2(80.0f, 50.0f));
    rectShader.Bind();
    rectShader.SetUniformMat4("projection", projection);



    Shader circleShader("../resources/shaders/CircleVertexShader.vs", "../resources/shaders/CircleFragmentShader.fs");
    core::Circle circ(glm::vec3(400.0f, 300.0f, 0.0f), glm::vec3(0.7f, 0.3f, 0.6), glm::vec2(50.0f, 50.0f), true, 50);
    //core::Circle cir(glm::vec3(400.0f, 600.0f, 0.0f), glm::vec2(50.0f, 50.0f), true, 30, "../resources/textures/awesomeface.png");
    circleShader.Bind();
    circleShader.SetUniformMat4("projection", projection);
    circleShader.SetUniformMat4("world", glm::mat4(1));


    std::thread thread(&Application::call_from_thread, this);
    mainTimer->getElapsedTime();
    std::thread thread2(&Application::fpsUpdate, this, fps, mainTimer);
    while(!m_Window->Closed())
    {
        mainTimer->getElapsedTime();

        m_Window->Clear();

        rect1.Draw(rectangleShader);
        rect2.Draw(rectangleShader);
        rect3.Draw(rectShader);
        //cir.Draw(circleShader);
        circ.Draw(circleShader);


        fps->renderText();

        m_Window->Render();
    }
    delete(fps);
    delete(mainTimer);
    thread.join();
    thread2.join();
}


