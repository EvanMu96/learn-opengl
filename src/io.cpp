#include "io.h"
#include "spdlog/spdlog.h"

#define SUCC 1
#define FAIL 0

constexpr size_t gLogBuffSize = 512;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path): m_program(0)
{
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vshader_file;
	std::ifstream fshader_file;

	vshader_file.exceptions(std::ifstream::badbit);
	fshader_file.exceptions(std::ifstream::badbit);

	try
	{
		vshader_file.open(vertex_path);
		fshader_file.open(fragment_path);
		std::stringstream vshader_stream, fshader_stream;

		vshader_stream << vshader_file.rdbuf();
		fshader_stream << fshader_file.rdbuf();
		
		vertex_code = vshader_stream.str();
		fragment_code = fshader_stream.str();
	}
	catch (const std::ifstream::failure e)
	{
		spdlog::error("CANNOT OPEN SHADER PROGRAM.");
	}

	auto vshader_buff = vertex_code.c_str();
	auto fshader_buff = fragment_code.c_str();

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	__init_shader(vertex, &(vshader_buff));
	__init_shader(fragment, &(fshader_buff));

	m_program = glCreateProgram();
	glAttachShader(m_program, vertex);
	glAttachShader(m_program, fragment);
	glLinkProgram(m_program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(m_program);
}

void Shader::__init_shader(GLuint shader, const GLchar* const* shader_src)
{
	GLint succ = FAIL;
	GLchar logBuff[gLogBuffSize];

	glShaderSource(shader, 1, shader_src, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &succ);
	if (!succ)
	{
		glGetShaderInfoLog(shader, gLogBuffSize, nullptr, logBuff);
		spdlog::error("failed to compile shader");
		spdlog::error("%s", logBuff);
	}
}
