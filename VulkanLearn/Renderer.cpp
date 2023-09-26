#include "Renderer.h"

#include <iostream>
#include <ostream>



Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

int Renderer::init(GLFWwindow* window)
{
	_window = window;
	try
	{
		create_instance();
		get_physical_device();
		create_logical_device();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
	return 0;
}

void Renderer::destroy()
{
		vkDestroyInstance(_instance, nullptr);
}

void Renderer::get_physical_device()
{
	//Get number of physical devices
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

	//If no devices available
	if (deviceCount == 0)
	{
		throw std::runtime_error("Can't find GPUs that support Vulkan Instance");
	}

	//Get list of physical devices
	std::vector<VkPhysicalDevice> deviceList(deviceCount);
	vkEnumeratePhysicalDevices(_instance, &deviceCount, deviceList.data());

	for (const auto& device : deviceList)
	{
		if (check_device_suitable(device))
		{
			_mainDevice.physicalDevice = device;
			break;
		}
	}

}

bool Renderer::check_device_suitable(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	_queueFamilyIndice indices = get_queue_families(device);

	return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
		deviceFeatures.geometryShader && indices.is_complete();
}

void Renderer::create_instance()
{

	//Info about my application, developer convenience
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "VulkanLearn";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_2;

	//Create Vulkan Instance information
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;


	std::vector<const char*> extensions= std::vector<const char*>();
	//Get required extensions
	uint32_t extensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);
	for(size_t i=0;i<extensionCount;i++)
	{
				extensions.push_back(glfwExtensions[i]);
	}

	if(!check_instance_extension_support(&extensions))
	{
		throw std::runtime_error("VkInstance does not support required extensions");
	}

	createInfo.enabledExtensionCount = extensions.size();
	createInfo.ppEnabledExtensionNames = extensions.data();

	//TODO
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;

	VkResult result = vkCreateInstance(&createInfo, nullptr, &_instance);
	if (result != VK_SUCCESS) {
		throw std::runtime_error("Failed to create an instance");
	}
}

_queueFamilyIndice Renderer::get_queue_families(VkPhysicalDevice device)
{
	_queueFamilyIndice indices;
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyList.data());
	

	int i = 0;
	for(const auto &queueFamily : queueFamilyList)
	{
		if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
						indices._graphics_family = i;
		}

	//	VkBool32 presentationSupport = false;
		//vkGetPhysicalDeviceSurfaceSupportKHR(device, queueFamilyCount, NULL, &presentationSupport);
		//if(presentationSupport)
		//{
		//	indices._presentation_family = i;
		//}

		if(indices.is_complete())
		{
			break;
		}
		i++;
	}

	return indices;
}

void Renderer::create_logical_device()
{
	VkDeviceQueueCreateInfo queueCreateInfo = {};
}


bool Renderer::check_validation_layer_support()
{
	return false;
}

bool Renderer::check_instance_extension_support(std::vector<const char*>* checkExtension)
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	for(const auto &checkExtension: *checkExtension)
	{
				bool hasExtension = false;
				for(const auto &extension: extensions)
				{
					if(strcmp(checkExtension,extension.extensionName)==0)
					{
						hasExtension = true;
						break;
					}
				} if(!hasExtension)
				{
					return false;
				}
	}

	return true;
}

