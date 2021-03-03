#include <iostream>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

#include "io.h"

constexpr GLfloat vertices[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};

// 使用 vertices 的索引，避免重复点占用内存
constexpr GLuint indices[] = {
	0, 1, 3, 1, 2, 3
};

void render_loop(GLFWwindow* window, Shader& shader, GLuint VAO, GLuint VBO)
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.Use();
		glBindVertexArray(VAO);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// release VAO
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
		std::this_thread::sleep_for(std::chrono::seconds(1));
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
		std::cout << "Failed to create GLFW window" << std::endl;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	Shader shader("vshader.v", "fshader.f");

	render_loop(window, shader, VAO, VBO);

	glfwTerminate();
	return 0;
}