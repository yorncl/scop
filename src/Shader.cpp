#include "Shader.hpp"
#include <fstream>
#include <iterator>
#include <exception>
#include <iostream>

struct ShaderCompilationError : std::exception
{
	const char* what() const throw()
	{
		return "An error has occured while compiling shaders";
	}
};

Shader::Shader()
{
}

Shader::Shader(unsigned int type) : _type(type)
{
}

void Shader::from_file(const std::string& filename)
{

	std::ifstream is;
	is.open(filename);
	if(!is.is_open())
		throw std::runtime_error("Error while opening file");
	_source.assign(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>()); 
}

void Shader::compile()
{
	_id = glCreateShader(_type);
	const char* const ptr = _source.c_str();
	glShaderSource(_id, 1, &ptr, NULL);
	glCompileShader(_id);

	int res;
	glGetShaderiv(_id, GL_COMPILE_STATUS, &res);
	char infoLog[512]; // TODO change this 
	glGetShaderInfoLog(_id, 512, NULL, infoLog);
	infoLog[511] = 0; // TODO very hacky
	fprintf(stderr, "%s", infoLog);
	if (res == GL_FALSE)
		throw ShaderCompilationError();
}
