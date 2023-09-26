#pragma once

struct _queueFamilyIndice
{
	int _graphics_family = -1;
	int _presentation_family = -1;

	bool is_complete() const
	{
				return _graphics_family >= 0 && _presentation_family >= 0;
	}
};

class Utilities
{
};

