#include "Context.hpp"

Context::Context(GLFWwindow *w, Object *o)
{
	window = w;
	transition = false;
	direction = false;
	textCoeff = 0;
	obj = o;
}

Context::~Context()
{
}
