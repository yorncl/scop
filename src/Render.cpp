#include "Render.hpp"
#include <stb_image.h>
#include <exception>
#include <cstdlib>
#include <ctime>
#include "Mat4.hpp"

bool transition = false;
bool direction = true;
std::clock_t startime;

Render::Render(GLFWwindow *window, Object* obj) : _window(window), _obj(obj)
{

	glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Cannot instantiate GLAD");
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
		fprintf(stderr, "%s", infoLog);
	}

	// TODO error management
	glValidateProgram(_shader_program);
	glUseProgram(_shader_program);

	glDeleteShader(_vs._id); // TODO might crash ?
	glDeleteShader(_fs._id);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void) key;
	(void) scancode;
	(void) action;
	(void) mods;
	(void) window;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	    exit(0);
	if (key == GLFW_KEY_T && action == GLFW_RELEASE && !transition)
	{
		startime = std::clock();
		transition = true;
	}
}

void Render::render_loop()
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

	//Matrices and transhform uniforms
	Mat4 m = Mat4::new_identity();
	unsigned int modelm = glGetUniformLocation(_shader_program, "modelm");
	glUniformMatrix4fv(modelm, 1, GL_FALSE, m.data());
	m = Mat4::new_scale(2.0f, 2.0f, 2.0f);
	unsigned int textCoeff = glGetUniformLocation(_shader_program, "textCoeff");
	glUniform1f(textCoeff, 1.0f);

	// Enable vertex attrib
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

	// texture stuff
	int width, height, nrChannels;
	unsigned char *data = stbi_load("resources/cobble.jpg", &width, &height, &nrChannels, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// faces
	if(_obj->indices.size() > 0)
	{
		glGenBuffers(1, &_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _obj->indices.size() * sizeof(GLuint), _obj->indices.data(), GL_STATIC_DRAW);
	}

	glfwSetKeyCallback(_window, key_callback);
	while(!glfwWindowShouldClose(_window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		if (transition)
		{
			float elapsed = float(std::clock() - startime);
			if (elapsed >= 100000)
			{
				direction = !direction;
				transition = false;
			}
			else
			{
				glUniform1f(textCoeff, direction ? 1.0f - elapsed/100000 : elapsed/100000);
			}
		}
	
		glUseProgram(_shader_program);

		float time = glfwGetTime();
		unsigned int angleLoc = glGetUniformLocation(_shader_program, "angle");
		glUniform1f(angleLoc, time);

		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawElements(GL_TRIANGLES, _obj->indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(_window);
		glfwPollEvents(); 
	}
}
