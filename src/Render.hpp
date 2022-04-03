#ifndef RENDER_HPP
#define RENDER_HPP

#include <ctime>
#include "Shader.hpp"
#include "Object.hpp"
#include "Mat4.hpp"
#include "Context.hpp"

class Render
{
	private:
		Context* _ctx;
		GLuint _VAO;
		GLuint _VBO;
		GLuint _EBO;
		Shader _vs;
		Shader _fs;
		GLuint _shader_program;

	public:
		Render(Context *ctx);

		void load_shaders();
		void compile_program();
		void render_loop();

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void load_buffers();
		void init_uniforms();
		void load_texture();
		void update_uniforms();

		struct ShaderError;
};

#endif
