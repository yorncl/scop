#include <ctime>
#include "Input.hpp"
#include "Context.hpp"

#define TRANS_DELTA 5.0f

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Context* ctx = (Context*)glfwGetWindowUserPointer(window);
	(void) scancode;
	(void) mods;

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
			exit(0);
		}
		// X
		if (key == GLFW_KEY_A)
			ctx->input |= XNEG;
		if (key == GLFW_KEY_D)
			ctx->input |= XPOS;
		// Y
		if (key == GLFW_KEY_J)
			ctx->input |= YNEG;
		if (key == GLFW_KEY_K)
			ctx->input |= YPOS;
		// Z
		if (key == GLFW_KEY_W)
			ctx->input |= ZNEG;
		if (key == GLFW_KEY_S)
			ctx->input |= ZPOS;
		if (key == GLFW_KEY_T)
			ctx->input |= TRANSITIONSTART;
	}

	if (action == GLFW_RELEASE)
	{
		// X
		if (key == GLFW_KEY_A)
			ctx->input ^= XNEG;
		if (key == GLFW_KEY_D)
			ctx->input ^= XPOS;
		// Y
		if (key == GLFW_KEY_J)
			ctx->input ^= YNEG;
		if (key == GLFW_KEY_K)
			ctx->input ^= YPOS;
		// Z
		if (key == GLFW_KEY_W)
			ctx->input ^= ZNEG;
		if (key == GLFW_KEY_S)
			ctx->input ^= ZPOS;
		if (key == GLFW_KEY_T)
			ctx->input ^= TRANSITIONSTART;
	}

	if (key == GLFW_KEY_T && !ctx->transition)
	{
		ctx->startime = std::clock();
		ctx->transition = true;
	}
}

void Input::resize_callback(GLFWwindow* window, int width, int height)
{
	Context* ctx = (Context*)glfwGetWindowUserPointer(window);
	ctx->updateWindowSize(width, height);
}



