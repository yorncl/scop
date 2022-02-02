#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <exception>
#include <iostream>
#include <vector>

#include "Vec3.hpp"

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
	std::vector<Vec3<float>> vertices;
	std::vector<unsigned int> indices; // TODO indices can be negative innit ?
	std::vector<Vec3<float>> normals;
	friend std::ostream& operator<<(std::ostream& os, Object& obj);
};

#endif
