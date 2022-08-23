#include "OnKeyEventListener.h"

bool OnKeyEventListener::keys[GLFW_KEY_LAST]		= { 0 };
bool OnKeyEventListener::keysChanged[GLFW_KEY_LAST] = { 0 };

void OnKeyEventListener::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_RELEASE)
	{
		if (!keys[key])
		{
			keys[key] = true;
		}
	}
	else
		keys[key] = false;
	keysChanged[key] = true;
}

bool OnKeyEventListener::key(int key)
{
	return keys[key];
}

bool OnKeyEventListener::keyChanged(int key)
{
	bool ret = keysChanged[key];
	keysChanged[key] = false;
	return ret;
}

bool OnKeyEventListener::keyWentUp(int key)
{
	return !keys[key] && keyChanged(key);
}

bool OnKeyEventListener::keyWentDown(int key)
{
	return keys[key] && keyChanged(key);

}
