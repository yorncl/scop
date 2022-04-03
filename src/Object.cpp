#include <iostream>
#include "Object.hpp"
#include "Mat4.hpp"

Object::Object()
{
	transform.translate = Mat4<float>::new_translate(0, 0, 0);
}

Object::~Object()
{

}

void Object::translate(float x, float y, float z)
{
	Mat4<float>& m = transform.translate;
	m[3][0] += x; 
	m[3][1] += y; 
	m[3][2] += z; 
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
