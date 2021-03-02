#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

#include "io.h"

constexpr GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

const char* vertex_shader_inline =
"#version 400\n"
"in vec3 vp;\n"
"void main() {\n"
"gl_Position = vec4(vp, 1.0);\n"
"}\n";

const char* fragment_shader_inline =
"#version 400\n"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(0.0, 0.5, 0.5, 1.0);"
"}";

void render_loop(GLFWwindow* window, GLuint shader_program, GLuint VAO, GLuint VBO)
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// update other events like input handling 
		glfwPollEvents();

		glfwSwapBuffers(window);
	}
}

void init_shader(GLuint shader, const char* const* shader_src)
{
	glShaderSource(shader, 1, shader_src, nullptr);
	glCompileShader(shader);
}

int main()
{
	spdlog::info("Initializing OpenGL");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewInit();

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO); // VBO 对象 Vertex Buffer Object
	glGenVertexArrays(1, &VAO); // VAO 对象 Vertex Array Object
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	init_shader(vs, &vertex_shader_inline);
	init_shader(fs, &fragment_shader_inline);

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, fs);
	glAttachShader(shader_program, vs);
	glLinkProgram(shader_program);
	
	// 删除不用的 Shader 防止再次使用
	glDeleteShader(fs);
	glDeleteShader(vs);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	render_loop(window, shader_program, VAO, VBO);

	glfwTerminate();
	return 0;
}