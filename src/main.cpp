#include <iostream>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

#include "io.h"

GLfloat vertices[] = {
	// 位置              // 颜色
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};

// 使用 vertices 的索引，避免重复点占用内存
constexpr GLuint indices[] = {
	0, 1, 2
};

void render_loop(GLFWwindow* window, Shader& shader, GLuint VAO, GLuint VBO)
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.Use();

		// 使用 uniform 更新传递到 shader program 的变量
// 		GLfloat time_value = static_cast<GLfloat>(glfwGetTime());
// 		GLfloat green_value = (sin(time_value) / 2) + 0.5f;
// 		GLint vertex_color_loc = glGetUniformLocation(shader.GetShader(), "ourColor");
// 		glUniform4f(vertex_color_loc, 0.0f, green_value, 0.0f, 1.0f);

		// draw
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	}
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
		spdlog::error("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewInit();

	GLuint VBO, VAO, EBO;

	glGenBuffers(1, &VBO); // VBO 对象 Vertex Buffer Object
	glGenVertexArrays(1, &VAO); // VAO 对象 Vertex Array Object
	glGenBuffers(1, &EBO); // EBO 对象

	// initialize
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	Shader shader("shaders/vshader.v", "shaders/fshader.f");

	render_loop(window, shader, VAO, VBO);

	glfwTerminate();
	return 0;
}