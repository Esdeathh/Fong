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
    while(!m_Window->Closed())
    {
        m_Window->Update();
    }
}
