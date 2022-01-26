#ifndef OBJECT_HPP
#define OBJECT_HPP

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
	std::vector<unsigned int> indices; // TODO indices can be negative innit ?
	friend std::ostream& operator<<(std::ostream& os, Object& obj);
};

#endif
