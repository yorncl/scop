#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <exception>
#include <iostream>
#include <vector>

#include "Vec3.hpp"
#include "Mat4.hpp"
#include "Quat4.hpp"

struct ObjetMalformed : public std::exception
{
	const char* what() const throw() {
		return "The object is malformed";
	}
};

class Transform
{
	public:
		Mat4<float> translate;
		Quat4 rotation;
		Vec3<double> scale;

		Transform(){};
		~Transform(){};
};

class ObjData {
	public:
		std::vector<Vec3<float>> vertices;
		std::vector<int> indices;
		std::vector<Vec3<float>> normals;
};

class Object
{
	public:
		Transform transform;
		ObjData data;
		std::string name;
		Object();
		~Object();
		void translate(float x, float y, float z);
		void readjustVertices();

		friend std::ostream& operator<<(std::ostream& os, Object& obj);
};

#endif
