#ifndef RENDER_HPP
#define RENDER_HPP

#include "Shader.hpp"

class Render
{
	public:
		GLFWwindow* window;
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		Shader vs;
		Shader fs;
		GLuint shader_program;
}

#endif
