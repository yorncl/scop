#include <stb_image.h>
#include <exception>
#include <cstdlib>
#include <ctime>
#include "Mat4.hpp"
#include "Render.hpp"

struct Render::ShaderError : public std::exception
{
	const char* what() const throw() {
		return "A shader error has occured";
	}
};

Render::Render(Context* ctx)
{
	_ctx = ctx;
	glfwMakeContextCurrent(_ctx->window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Cannot instantiate GLAD");
	load_shaders();
	compile_program();
	load_buffers();
	init_uniforms();
	load_texture();
}

void Render::load_shaders()
{
	_vs = Shader(GL_VERTEX_SHADER);
	_fs = Shader(GL_FRAGMENT_SHADER);
	_vs._type = GL_VERTEX_SHADER;
	_fs._type = GL_FRAGMENT_SHADER;
	_vs.from_file("src/shaders/vertex.glsl");
	_fs.from_file("src/shaders/fragment.glsl");
}

void check_status(int id, int status) throw()
{
	int success = 1;
	glGetProgramiv(id, status, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		infoLog[511] = 0;
		std::cerr << infoLog << std::endl;
		throw Render::ShaderError();
	}
}

void Render::compile_program()
{
	//compile shaders
	_vs.compile();
	_fs.compile();

	// create shader program
	_shader_program = glCreateProgram();

	// attach shader to program
	glAttachShader(_shader_program, _vs._id);
	glAttachShader(_shader_program, _fs._id);
	glLinkProgram(_shader_program);

	check_status(_shader_program, GL_LINK_STATUS);
	glValidateProgram(_shader_program);
	check_status(_shader_program, GL_VALIDATE_STATUS);
	glUseProgram(_shader_program);

	glDeleteShader(_vs._id);
	glDeleteShader(_fs._id);
}


void Render::load_buffers()
{

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// Vertex positions
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _ctx->obj->data.vertices.size() * sizeof(Vec3<float>), _ctx->obj->data.vertices.data() , GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3<float>), 0);

	// Enable vertex attrib
        glEnableVertexAttribArray(0);

	// faces
	if(_ctx->obj->data.indices.size() > 0)
	{
		glGenBuffers(1, &_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _ctx->obj->data.indices.size() * sizeof(GLuint), _ctx->obj->data.indices.data(), GL_STATIC_DRAW);
	}
}

void Render::init_uniforms()
{
	// identifier to reference uniforms
	unsigned int matrix;
	Object* obj = _ctx->obj;

	// model matrix (object to world position)
	matrix = glGetUniformLocation(_shader_program, "modelm");
	glUniformMatrix4fv(matrix, 1, GL_FALSE, obj->transform.translate.data());

	// view matrix (world to camera position)
	matrix = glGetUniformLocation(_shader_program, "viewm");
	glUniformMatrix4fv(matrix, 1, GL_FALSE, _ctx->viewm.data());

	matrix = glGetUniformLocation(_shader_program, "projm");
	glUniformMatrix4fv(matrix, 1, GL_FALSE, _ctx->projm.data());

	// Color-texture blending parameter
	_textCoeff = glGetUniformLocation(_shader_program, "textCoeff");
	glUniform1f(_textCoeff, 0.0f);
}

void Render::load_texture()
{
	// Loading the cobblestone texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("resources/kitten.jpeg", &width, &height, &nrChannels, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

void Render::update_uniforms()
{
	// TODO, may be not a good idea to update uniforms each frame
	// even thought it isn't really necessary for a project of this scale
	glUniform1f(_textCoeff, _ctx->transitionParam);
	unsigned int matrix = glGetUniformLocation(_shader_program, "modelm");
	glUniformMatrix4fv(matrix, 1, GL_FALSE, _ctx->modelm.data());
	// binding shader program TODO is it necessary ?
	glUseProgram(_shader_program);

	matrix = glGetUniformLocation(_shader_program, "projm");
	glUniformMatrix4fv(matrix, 1, GL_FALSE, _ctx->projm.data());
}

void Render::render_loop()
{
	while(!glfwWindowShouldClose(_ctx->window))
	{
		// Clear
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		// update the state
		_ctx->update();
		update_uniforms();

		glDrawElements(GL_TRIANGLES, _ctx->obj->data.indices.size(), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(_ctx->window);
		glfwPollEvents(); 
	}
}
