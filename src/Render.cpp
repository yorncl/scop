#include "Render.hpp"
#include <stb_image.h>
#include <exception>

Render::Render(GLFWwindow *window, Object* obj) : _window(window), _obj(obj)
{

	glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Cannot instantiate GLAD");
}

void Render::load_shaders()
{
	_vs = Shader(GL_VERTEX_SHADER);
	_vs = Shader(GL_FRAGMENT_SHADER);
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
	int success;
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


void Render::render_loop()
{

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);

	// binding the vertex array object and its buffer
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _obj->vertices.size(), _obj->vertices.data(), GL_STATIC_DRAW);
	// vertex attrib pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _obj->indices.size(), _obj->indices.data(), GL_STATIC_DRAW);
	}
        glEnableVertexAttribArray(0);

	while(!glfwWindowShouldClose(_window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glUseProgram(_shader_program);

		float time = glfwGetTime();
		unsigned int angleLoc = glGetUniformLocation(_shader_program, "angle");
		glUniform1f(angleLoc, time);

		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, 1, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(_window);
		glfwPollEvents(); 
	}
}
