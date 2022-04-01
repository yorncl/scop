#ifndef RENDER_HPP
#define RENDER_HPP

#include <ctime>
#include "Shader.hpp"
#include "Object.hpp"
#include "Mat4.hpp"

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
		Mat4 _modelm;
		Mat4 _viewm;
		Mat4 _projm;

		Render(GLFWwindow *win, Object *obj);

		void load_shaders();
		void compile_program();
		void render_loop();

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void load_buffers();
		void init_uniforms();
		void load_texture();
		void update_uniforms();

		// Not really pretty but hey, it works
		static bool _transition;
		static bool _direction;
		static unsigned int _textCoeff;
		static std::clock_t _startime;
};

#endif
