#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include "GLFW/glfw3.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Shader Àà£¬·â×° OpenGL Shader
class Shader
{
public:
	Shader(const GLchar* vertex_path, const GLchar* fragment_path);
	void Use();
	GLint GetShader() const;
private:
	void __init_shader(GLuint shader, const GLchar* const* shader_src);
	GLuint m_program;
};