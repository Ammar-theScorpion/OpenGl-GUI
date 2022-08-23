#pragma once
#include"GL/glew.h"
#include"GLFW/glfw3.h"
class vertexBuffer {
public:

	vertexBuffer(const void* indecies, int size, int type);
	~vertexBuffer();
	void bind()const;
	void unbind()const;

private:
	unsigned int m_Renderer;
};