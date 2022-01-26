#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
	public:
	std::string _source;
	unsigned int _type;
	unsigned int _id;
	

	//TODO Coplien form ?
	Shader();
	Shader(unsigned int type);
	
	void compile();
	void from_file(const std::string& filename);
};

#endif
