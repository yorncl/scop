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
	Mat4 translate;
	Quat4 rotation;
	Vec3<double> scale;

	Transform();
	~Transform();
};

class Object
{
	public:
		Transorm transform;
		struct data {
			std::string name;
			std::vector<Vec3<float>> vertices;
			std::vector<int> indices;
			std::vector<Vec3<float>> normals;
		}
		Object();
		~Object();
		void readjustVertices();
		friend std::ostream& operator<<(std::ostream& os, Object& obj);
};

#endif
