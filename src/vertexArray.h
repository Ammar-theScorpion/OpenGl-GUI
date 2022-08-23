#pragma once
#include"vertexBuffer.h"
#include"vertexLayoutBuffer.h"
class vertexArray {
public:
 
	void addBuffer(const vertexBuffer& vbo, const vertexLayout& vlb);
private:
	unsigned int m_Renderer;

};