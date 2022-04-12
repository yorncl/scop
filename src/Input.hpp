#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>

#define XPOS (1 << 0)
#define XNEG (1 << 1)
#define YPOS (1 << 2)
#define YNEG (1 << 3)
#define ZPOS (1 << 4)
#define ZNEG (1 << 5)
#define TRANSITIONSTART (1 << 6)
#define SCALEUP (1 << 7)
#define SCALEDOWN (1 << 8)

namespace Input
{
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void resize_callback(GLFWwindow* window, int width, int height);
};
#endif
