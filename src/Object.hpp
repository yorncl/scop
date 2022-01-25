#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <GLFW/glfw3.h>
#include <exception>
#include <iostream>
#include <vector>

struct ObjetMalformed : public std::exception
{
	const char* what() const throw() {
		return "The object is malformed";
	}
};

class Object
{
	public:
	std::string name;
	std::vector<float> vertices;
	std::vector<int> indices;
	friend std::ostream& operator<<(std::ostream& os, Object& obj);
};

#endif
