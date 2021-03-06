//
// Created by Rafik on 04.11.2018.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <core/Window.h>
#include <core/Mesh.h>
#include <core/Shader.h>
#include <core/Texture.h>
#include <common/timer.h>
#include <iostream>
#include <thread>
#include <core/Font.h>
#include <sstream>
#include <core/Player.h>

const int FPS_MAX = 60;

class Application
{
private:
    Window *m_Window;
public:
    Application(const std::string & title, int width, int height, bool fullscreen = false);
    ~Application();
private:
    bool Init(const std::string & title, int width, int height, bool fullscreen = false);
    void Run();
    void call_from_thread();
    void fpsUpdate(Font *font, Timer *timer);
};

#endif //APPLICATION_H
