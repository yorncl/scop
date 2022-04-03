#include "Object.hpp"
#include <iostream>

Object::Object()
{

}

Object::~Object()
{

}

void Object::readjustVertices()
{
	size_t nv = data.vertices.size();
	double ax = 0, ay = 0, az = 0;
	for (size_t i = 0; i < nv; i++)
	{
		ax += data.vertices[i].x;
		ay += data.vertices[i].y;
		az += data.vertices[i].z;
	}
	ax /= nv;
	ay /= nv;
	az /= nv;
	for (size_t i = 0; i < nv; i++)
	{
		data.vertices[i].x -= ax;
		data.vertices[i].y -= ay;
		data.vertices[i].z -= az;
 	}
}

std::ostream& operator<<(std::ostream& os, Object& obj)
{
	os << "Object name : " << obj.name << std::endl;
	os << "\t" << "Number of vertices :"  << obj.data.vertices.size()/3 << std::endl;
	os << "\t" << "Number of indices :"  << obj.data.indices.size() << std::endl;
	return os;
}
