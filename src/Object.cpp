#include "Object.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, Object& obj)
{
	(void) obj;
	os << "Logging the object" << std::endl;
	return os;
}
