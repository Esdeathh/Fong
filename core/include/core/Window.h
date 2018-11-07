//
// Created by Rafik on 04.11.2018.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <common/timer.h>

class Window
{
private:
    std::string m_Title;
    int m_Width, m_Height;
    GLFWwindow *m_Window;
    bool m_Fullscreen;
public:
    Window(const std::string & title, int width, int height, bool fullscreen = false);
    ~Window();
    void Render();
    bool Closed();
    void Clear();
    void ProcessInput();
private:
    bool Init();
};

#endif //WINDOW_H
