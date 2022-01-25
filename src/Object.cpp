#include "Object.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, Object& obj)
{
	os << "Object name : " << obj.name << std::endl;
	os << "\t" << "Number of vertices :"  << obj.vertices.size()/3 << std::endl;
	os << "\t" << "Number of indices :"  << obj.indices.size() << std::endl;
	return os;
}
