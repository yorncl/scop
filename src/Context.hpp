#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <ctime>

#include <GLFW/glfw3.h>
#include "Mat4.hpp"
#include "Object.hpp"

class Context
{
	public:
		GLFWwindow* window; // reference to the window
		Object* obj; // the object to be displayed

		Mat4<float> modelm;
		Mat4<float> viewm;
		Mat4<float> projm;

		// TODO is there a cleaner way ?
		bool transition;
		bool direction;
		unsigned int textCoeff;
		std::clock_t startime;

		Context(GLFWwindow* w, Object* o);
		~Context();
};

#endif
