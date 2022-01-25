#include <iostream>
#include <GLFW/glfw3.h>
#include "Object.hpp"
#include "Parser.hpp"

#define WINDOW_INIT_WIDTH 500
#define WINDOW_INIT_HEIGHT 500

static void glfw_error_callback(int code, const char* msg)
{
	fprintf(stderr, "GLFW ERROR %d : %s\n", code, msg);
}

static GLFWwindow* init_window()
{
        glfwInit();
	glfwSetErrorCallback(glfw_error_callback);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return glfwCreateWindow(WINDOW_INIT_WIDTH, WINDOW_INIT_HEIGHT, "scop", NULL, NULL);
}

int main(int ac, char** av)
{

	if (ac != 2)
	{
		std::cerr << "Usage : ./scop [object_file]" << std::endl;
		return 1;
	}
	// Trying to parse
	Object *obj;
	try 
	{
		obj = Parser::read_obj(av[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error while parsing" << std::endl;
		return 1;
	}

	// Logging the parsed object
	std::cout << *obj << std::endl;

	// Creating the window
	GLFWwindow *window = init_window();

	glfwDestroyWindow(window);
	glfwTerminate();
	delete obj;
}
