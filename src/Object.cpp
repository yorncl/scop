#include "Object.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, Object& obj)
{
	os << "Object name : " << obj.name << std::endl;
	os << "\t" << "Number of vertices :"  << obj.vertices.size()/3 << std::endl;
	return os;
}
