#include <ctime>
#include "Input.hpp"
#include "Context.hpp"

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void) scancode;
	(void) mods;
	Context* context = (Context*)glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	    	exit(0);
	}
	if (key == GLFW_KEY_T && action == GLFW_RELEASE && !context->transition)
	{
		context->startime = std::clock();
		context->transition = true;
	}
}
