#ifndef PARSER_HPP
#define PARSER_HPP

#include "Object.hpp"

class Parser 
{
	public:
	static Object* read_obj(char *filename);
};

#endif
