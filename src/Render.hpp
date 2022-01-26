#ifndef RENDER_HPP
#define RENDER_HPP

#include "Shader.hpp"
#include "Object.hpp"

class Render
{
	public:
		GLFWwindow* _window;
		Object* _obj;
		GLuint _VAO;
		GLuint _VBO;
		GLuint _EBO;
		Shader _vs;
		Shader _fs;
		GLuint _shader_program;

		Render(GLFWwindow *win, Object *obj);

		void load_shaders();
		void compile_program();
		void render_loop();
};

#endif
