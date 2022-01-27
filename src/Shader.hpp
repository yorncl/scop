#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
	public:
	std::string _source;
	GLuint _type;
	unsigned int _id;
	std::string _filename;
	

	//TODO Coplien form ?
	Shader();
	Shader(const Shader&);
	Shader(unsigned int type);
	
	Shader& operator=(const Shader& s);
	
	void compile();
	void from_file(const std::string& filename);
};

#endif
