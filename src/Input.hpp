#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>

namespace Input
{
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
#endif
