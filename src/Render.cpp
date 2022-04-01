#include "Render.hpp"
#include <stb_image.h>
#include <exception>
#include <cstdlib>
#include <ctime>
#include "Mat4.hpp"

bool Render::_transition = false;
bool Render::_direction = false;
unsigned int Render::_textCoeff;
std::clock_t Render::_startime;

Render::Render(GLFWwindow *window, Object* obj) : _window(window), _obj(obj)
{
	glfwSetKeyCallback(window, this->key_callback);
	glfwMakeContextCurrent(window);
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

	// check the linking status
	int success = 1;
	glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512]; // TODO change this 
		glGetProgramInfoLog(_shader_program, 512, NULL, infoLog);
		infoLog[511] = 0; // TODO very hacky
		std::cerr << infoLog << std::endl;
	}

	// TODO error management
	glValidateProgram(_shader_program);
	glUseProgram(_shader_program);

	glDeleteShader(_vs._id); // TODO might crash ?
	glDeleteShader(_fs._id);
}

void Render::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void) scancode;
	(void) mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	    	exit(0);
	}
	if (key == GLFW_KEY_T && action == GLFW_RELEASE && !_transition)
	{
		_startime = std::clock();
		_transition = true;
	}
}

void Render::load_buffers()
{

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// Vertex positions
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _obj->vertices.size() * sizeof(Vec3<float>), _obj->vertices.data() , GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3<float>), 0);


	// Colors 
	unsigned int colors;
	glGenBuffers(1, &colors);
	glBindBuffer(GL_ARRAY_BUFFER, colors);
	std::vector<float> colors_buff;
	for (size_t i = 0; i < _obj->vertices.size() * 3; i++)
		colors_buff.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); // TODO seed on a static objet so I get the same result every time
	glBufferData(GL_ARRAY_BUFFER, colors_buff.size() * sizeof(float), colors_buff.data() , GL_STATIC_DRAW);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	// Normals
	for (auto it = _obj->vertices.begin(); it < _obj->vertices.end(); it++)
	{
		Vec3<float> normal = *it;
		normal.normalize();
		_obj->normals.push_back(normal);
	}
	unsigned int normals;
	glGenBuffers(1, &normals);
	glBindBuffer(GL_ARRAY_BUFFER, normals);
	glBufferData(GL_ARRAY_BUFFER, _obj->normals.size() * sizeof(Vec3<float>), _obj->normals.data() , GL_STATIC_DRAW); // TODO change datatype to make it more readable
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3<float>), 0);

	// Enable vertex attrib
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

	// faces
	if(_obj->indices.size() > 0)
	{
		glGenBuffers(1, &_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _obj->indices.size() * sizeof(GLuint), _obj->indices.data(), GL_STATIC_DRAW);
	}
}

void Render::init_uniforms()
{
	// identifier to reference uniforms
	unsigned int matrix;

	// model matrix (object to world position)
	matrix = glGetUniformLocation(_shader_program, "modelm");
	_modelm = Mat4::new_identity();
	glUniformMatrix4fv(matrix, 1, GL_FALSE, _modelm.data());

	// view matrix (world to camera position)
	matrix = glGetUniformLocation(_shader_program, "viewm");
	_viewm = Mat4::new_translate(0.0f, 0.0f, -5.0f);
	glUniformMatrix4fv(matrix, 1, GL_FALSE, _viewm.data());

	matrix = glGetUniformLocation(_shader_program, "projm");
	_projm = Mat4::new_projection();
	glUniformMatrix4fv(matrix, 1, GL_FALSE, _projm.data());

	// Color-texture blending parameter
	_textCoeff = glGetUniformLocation(_shader_program, "textCoeff");
	glUniform1f(_textCoeff, 0.0f);
}

void Render::load_texture()
{
	// Loading the cobblestone texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("resources/cobble.jpg", &width, &height, &nrChannels, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

void Render::update_uniforms()
{
	if (_transition)
	{
		float elapsed = float(std::clock() - _startime);
		if (elapsed >= 100000)
		{
			_direction = !_direction;
			_transition = false;
		}
		else
		{
			glUniform1f(_textCoeff, _direction ? 1.0f - elapsed/100000 : elapsed/100000);
		}
	}

	//updating the rotation of the object
	float time = glfwGetTime();
	(void) time;
	unsigned int matrix = glGetUniformLocation(_shader_program, "modelm");
	_modelm = Mat4::new_rotation(0.0f, -0.01f, 0.0f) * _modelm;
	glUniformMatrix4fv(matrix, 1, GL_FALSE, _modelm.data());
	// binding shader program TODO is it necessary ?
	glUseProgram(_shader_program);
}

void Render::render_loop()
{
	while(!glfwWindowShouldClose(_window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		update_uniforms();
		glDrawElements(GL_TRIANGLES, _obj->indices.size(), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(_window);
		glfwPollEvents(); 
	}
}
