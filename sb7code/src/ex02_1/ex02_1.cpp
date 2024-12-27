#include <sb7.h>

class simpleclear_app : public sb7::application
{
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Simple Clear";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    virtual void render(double currentTime)
    {
        //static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        //glClearBufferfv(GL_COLOR, 0, red);
        static const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);
    }
};

DECLARE_MAIN(simpleclear_app)
