#include "Renderer.h"

#include <iostream>

GLFWwindow* window;
Renderer renderer;
void initWindow(std::string wName = "Window", const int width = 800, const int height = 600)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);//no opengl context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);//no resizing

	window = glfwCreateWindow(800, 600, wName.c_str(), nullptr, nullptr);
}

int main()
{

	initWindow("Vulkan", 800, 600);
	if(renderer.init(window)==-1)
	{
				return -1;
	}

	while(!glfwWindowShouldClose(window))
	{
				glfwPollEvents();
	}

	renderer.destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}