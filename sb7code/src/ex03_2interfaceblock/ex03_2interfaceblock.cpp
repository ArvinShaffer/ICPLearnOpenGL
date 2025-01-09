#include <sb7.h>
#include <math.h>

class interfaceblock : public sb7::application
{
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Moving Triangle";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    virtual void startup()
    {
        static const char * vs_source[] = {
            "#version 450 core                                                  \n"
            "                                                                   \n"
            "layout (location = 0) in vec4 offset;                              \n"
            "layout (location = 1) in vec4 color;                               \n"
            "out VS_OUT                                                         \n"
            "{                                                                  \n"
            "    vec4 color;                                                    \n"
            "}vs_out;                                                           \n"
            "                                                                   \n"
            "void main(void)                                                    \n"
            "{                                                                  \n"
            "    const vec4 vectices[] = vec4[] (vec4( 0.25, -0.25, 0.5, 1.0),  \n"
            "                                    vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                    vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                   \n"
            "    gl_Position = vectices[gl_VertexID] + offset;                  \n"
            "    vs_out.color = color;                                          \n"
            "}                                                                  \n"
        };

        static const char * fs_source[] = 
        {
            "#version 450 core                       \n"
            "                                        \n"
            "in VS_OUT                               \n"
            "{                                       \n"
            "    vec4 color                          \n"
            "} fs_in;                                \n"
            "out vec4 color;                         \n"
            "                                        \n"
            "void main(void)                         \n"
            "{                                       \n"
            "    color = fs_in.color                 \n"
            "}                                       \n"
        };

        program = glCreateProgram();
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, fs_source, NULL);
        glCompileShader(fs);

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, vs_source, NULL);
        glCompileShader(vs);

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }
    virtual void render(double currentTime)
    {
        static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

        glUseProgram(program);
        GLfloat attrib[] = { (float)sin(currentTime) * 0.5f,
                             (float)cos(currentTime) * 0.6f,
                             0.0f, 0.0f };

        glVertexAttrib4fv(0, attrib);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    virtual void shutdown()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(program);
    }

private:
    GLuint program = 0;
    GLuint vao = 0;
};

DECLARE_MAIN(interfaceblock)