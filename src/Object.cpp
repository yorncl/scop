#include "Object.hpp"
#include <iostream>

void Object::calculateCenter()
{
	size_t nv = vertices.size();
	double ax = 0, ay = 0, az = 0;
	for (size_t i = 0; i < nv; i++)
	{
		ax += vertices[i].x;
		ay += vertices[i].y;
		az += vertices[i].z;
	}
	ax /= nv;
	ay /= nv;
	az /= nv;
	for (size_t i = 0; i < nv; i++)
	{
		vertices[i].x -= ax;
		vertices[i].y -= ay;
		vertices[i].z -= az;
 	}
}

std::ostream& operator<<(std::ostream& os, Object& obj)
{
	os << "Object name : " << obj.name << std::endl;
	os << "\t" << "Number of vertices :"  << obj.vertices.size()/3 << std::endl;
	os << "\t" << "Number of indices :"  << obj.indices.size() << std::endl;
	return os;
}
