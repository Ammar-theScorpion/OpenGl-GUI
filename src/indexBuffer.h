#pragma once
#include"GL/glew.h"
#include"GLFW/glfw3.h"
class indexBuffer {
public:

	indexBuffer(const void* indecies, int count, int type);
	~indexBuffer();
	void bind()const;
	void unbind()const;

private:
	unsigned int m_Renderer;
};