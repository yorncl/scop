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

		Mat4<float> viewm;
		Mat4<float> projm;
		Mat4<float> modelm;
		Mat4<float> scalem;

		float scaleFactor;
		bool transition;
		bool direction;
		std::clock_t startime;
		float transitionParam;

		size_t input;

		Context(GLFWwindow* w, Object* o);
		~Context();

		void update();
		void updateWindowSize(int w, int h);
};

#endif
