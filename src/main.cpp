#include <iostream>
#include "Object.hpp"
#include "Parser.hpp"
#include "Render.hpp"
#include "Input.hpp"

#define WINDOW_INIT_WIDTH 1000
#define WINDOW_INIT_HEIGHT 1000

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
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
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
		obj->readjustVertices();
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
	Context* ctx = new Context(window, obj);
	glfwSetKeyCallback(window, Input::key_callback);
	glfwSetWindowUserPointer(window, ctx);
	try
	{
		Render r(ctx);
		r.render_loop();
	}
	catch(std::exception &e)
	{
		std::cerr << "An error has occured while rendering" << std::endl;
		std::cerr << e.what() << std::endl;
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	delete obj;
	delete ctx;
}
