#include <sb7.h>

#define INTERPOLATE_COLOR

class colorfromposition : public sb7::application
{
	void init()
	{
		static const char title[] = "OpenGL SuperBible - Simple Color From Position";
		sb7::application::init();
		memcpy(info.title, title, sizeof(title));
	}

	virtual void startup()
	{
#ifndef	INTERPOLATE_COLOR
		static const char* vs_source[] =
		{
			"#version 450 core                                                   \n"
			"                                                                    \n"
			"void main(void)                                                     \n"
			"{                                                                   \n"
			"    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),    \n"
			"                                   vec4(-0.25, -0.25, 0.5, 1.0),    \n"
			"                                   vec4( 0.25,  0.25, 0.5, 1.0));   \n"
			"                                                                    \n"
			"    gl_Position = vertices[gl_VertexID];                            \n"
			"}                                                                   \n"
		};

		static const char* fs_source[] =
		{
			"#version 450 core                                                         \n"
			"                                                                          \n"
			"out vec4 color;                                                           \n"
			"void main(void)                                                           \n"
			"{                                                                         \n"
			"    color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,                  \n"
			"                 cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,                  \n"
			"                 sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.1),  \n"
			"                 1.0);                                                    \n"
			"}                                                                         \n"
		};
#else
		static const char* vs_source[] =
		{
			"#version 450 core                                                     \n"
			"                                                                      \n"
			"out vec4 vs_color;                                                    \n"
			"void main(void)                                                       \n"
			"{                                                                     \n"
			"    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),      \n"
			"                                   vec4(-0.25, -0.25, 0.5, 1.0),      \n"
			"                                   vec4( 0.25,  0.25, 0.5, 1.0));     \n"
			"    const vec4 colors[] = vec4[](vec4(1.0, 0.0, 0.0, 1.0),            \n"
			"                                 vec4(0.0, 1.0, 0.0, 1.0),            \n"
			"                                 vec4(0.0, 0.0, 1.0, 1.0));           \n"
			"    gl_Position = vertices[gl_VertexID];                              \n"
			"    vs_color = colors[gl_VertexID];                                   \n"
			"}                                                                     \n"
		};

		static const char* fs_source[] =
		{
			"#version 450 core                   \n"
			"                                    \n"
			"in vec4 vs_color;                   \n"
			"out vec4 color;                     \n"
			"                                    \n"
			"void main(void)                     \n"
			"{                                   \n"
			"    color = vs_color;               \n"
			"}                                   \n"
		};
#endif
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
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void shutdown()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteProgram(program);
	}
private:
	GLuint program;
	GLuint vao;
};

DECLARE_MAIN(colorfromposition)
