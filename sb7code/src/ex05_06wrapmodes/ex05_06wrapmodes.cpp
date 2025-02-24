#include <sb7.h>
#include <sb7ktx.h>

static const char* vs_source[] =
{
    "#version 410 core                                                              \n"
    "                                                                               \n"
    "uniform vec2 offset;                                                           \n"
    "                                                                               \n"
    "out vec2 tex_coord;                                                            \n"
    "                                                                               \n"
    "void main(void)                                                                \n"
    "{                                                                              \n"
    "    const vec4 vertices[] = vec4[](vec4(-0.45, -0.45, 0.5, 1.0),               \n"
    "                                   vec4( 0.45, -0.45, 0.5, 1.0),               \n"
    "                                   vec4(-0.45,  0.45, 0.5, 1.0),               \n"
    "                                   vec4( 0.45,  0.45, 0.5, 1.0));              \n"
    "                                                                               \n"
    "    gl_Position = vertices[gl_VertexID] + vec4(offset, 0.0, 0.0);              \n"
    "    tex_coord = vertices[gl_VertexID].xy * 3.0 + vec2(0.45 * 3);               \n"
    "}                                                                              \n"
};

static const char* fs_source[] =
{
    "#version 410 core                                                              \n"
    "                                                                               \n"
    "uniform sampler2D s;                                                           \n"
    "                                                                               \n"
    "out vec4 color;                                                                \n"
    "                                                                               \n"
    "in vec2 tex_coord;                                                             \n"
    "                                                                               \n"
    "void main(void)                                                                \n"
    "{                                                                              \n"
    "    color = texture(s, tex_coord);                                             \n"
    "}                                                                              \n"
};

class wrapmodes : public sb7::application
{
public:
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Texture Wrap Modes";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    void startup(void)
    {
        // Generate a name for the texture
        glGenTextures(1, &texture);

        // Load texture from file
        sb7::ktx::file::load("media/textures/rightarrows.ktx", texture);

        // Now bind it to the context using the GL_TEXTURE_2D binding point
        glBindTexture(GL_TEXTURE_2D, texture);

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

    void shutdown(void)
    {
        glDeleteProgram(program);
        glDeleteVertexArrays(1, &vao);
        glDeleteTextures(1, &texture);
    }

    void render(double t)
    {
        static const GLfloat green[] = { 0.0f, 0.1f, 0.0f, 1.0f };
        static const GLfloat yellow[] = { 0.4f, 0.4f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

        static const GLenum wrapmodes[] = { GL_CLAMP_TO_EDGE, GL_REPEAT, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT };
        static const float offsets[] = { -0.5f, -0.5f,
                                          0.5f, -0.5f,
                                         -0.5f,  0.5f,
                                          0.5f,  0.5f };

        glUseProgram(program);
        glViewport(0, 0, info.windowWidth, info.windowHeight);

        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, yellow);

        for (int i = 0; i < 4; i++)
        {
            glUniform2fv(0, 1, &offsets[i * 2]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapmodes[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapmodes[i]);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }

private:
    GLuint      texture;
    GLuint      program;
    GLuint      vao;
};

DECLARE_MAIN(wrapmodes);