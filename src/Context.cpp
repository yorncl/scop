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
	viewm = Mat4<float>::new_translate(0.0f, 0.0f, -5.0f);
	scaleFactor = 1.0f;
	scalem = Mat4<float>::new_identity() * scaleFactor;
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
	if (input & TRANSITIONSTART && !transition)
	{
		transition = true;
		startime = std::clock();
	}

	if (transition)
	{
		float elapsed = float(std::clock() - startime);
		transitionParam = direction ? 1.0f - elapsed/10000 : elapsed/10000;
		if (elapsed >= 10000)
		{
			direction = !direction;
			transition = false;
		}
	}
	if (input & SCALEUP)
	{
		scaleFactor += 0.05;
		scalem = Mat4<float>::new_identity() * scaleFactor;
		scalem[3][3] = 1.0f;
	}
	if (input & SCALEDOWN)
	{
		scaleFactor -= 0.05;
		if (scaleFactor < 0.1)
			scaleFactor = 0.05;
		scalem = Mat4<float>::new_identity() * scaleFactor;
		scalem[3][3] = 1.0f;
	}

	modelm = 
			obj->transform.translate
			* Mat4<float>::new_rotation(0.0f, (float)glfwGetTime() / M_PI_2, 0.0f) * scalem;
}

void Context::updateWindowSize(int w, int h)
{
	(void) w;
	(void) h;
	glViewport(0, 0, w, h);
	input = 0;
	projm = Mat4<float>::new_projection(90, (double)w/h);
}

Context::~Context()
{
}
