#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <tuple>

#include <GL/glew.h>
#include "GLFW/glfw3.h"

typedef unsigned char byte;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

class TextureImage
{
public:
	TextureImage(const GLchar* image_path);
	GLuint GetTexture() const;
private:
	GLuint m_texture;
};

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