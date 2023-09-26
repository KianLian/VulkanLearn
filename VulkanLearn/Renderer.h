#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>

#include "Utilities.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	int init(GLFWwindow* window);
	void destroy();
private:
	GLFWwindow* _window;
	//Vulkan stuffs
	VkInstance _instance;

	struct
	{
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;
	} _mainDevice;

	void get_physical_device();
	bool check_device_suitable(VkPhysicalDevice device);
	bool check_validation_layer_support();
	bool check_instance_extension_support(std::vector<const char*>* checkExtension);

	void create_instance();
	_queueFamilyIndice get_queue_families(VkPhysicalDevice device);


	void create_logical_device();
	
};

