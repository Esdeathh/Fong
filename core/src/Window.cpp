//
// Created by Rafik on 04.11.2018.
//

#include <Window.h>
/*
void ResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}*/

Window::Window(const std::string &title, int width, int height, bool fullscreen)
    : m_Title(title), m_Width(width), m_Height(height), m_Fullscreen(fullscreen)
{
    Init();
}

Window::~Window()
{
    glfwTerminate();
}

void Window::Update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
    ProcessInput();
}

bool Window::Init()
{
    if (!glfwInit())
    {
        std::cout << "FAILED to initialize glfw" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(m_Fullscreen)
        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    else
        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

    if(!m_Window)
    {
        glfwTerminate();
        std::cout << "FAILED to initialize Window" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(m_Window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "FAILED to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, m_Width, m_Height);
    //glfwSetFramebufferSizeCallback(m_Window, ResizeCallback);
    glfwSwapInterval(1);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    return true;
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

bool Window::Closed()
{
    return glfwWindowShouldClose(m_Window) == 1;
}

void Window::ProcessInput()
{
    if(glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);
}
