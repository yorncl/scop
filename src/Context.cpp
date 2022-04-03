#include "Context.hpp"
#include "Input.hpp"

Context::Context(GLFWwindow *w, Object *o)
{
	window = w;
	transition = false;
	direction = false;
	obj = o;
	input = 0;
	transitionParam = 0;
}

// updates the context based on :
// - keyboard movement input
// - animation state
void Context::update()
{
	// TODO, check online, this way seems ugly
	// update translation
	obj->translate(
			(input & XPOS ? 0.1f : 0) + (input & XNEG ? -0.1f : 0), 
			(input & YPOS ? 0.1f : 0) + (input & YNEG ? -0.1f : 0), 
			(input & ZPOS ? 0.1f : 0) + (input & ZNEG ? -0.1f : 0)
			);

	if (transition)
	{
		float elapsed = float(std::clock() - startime);
		if (elapsed >= 10000)
		{
			direction = !direction;
			transition = false;
			transitionParam = direction ? 1.0f - elapsed/10000 : elapsed/10000;
		}
	}
}

Context::~Context()
{
}
