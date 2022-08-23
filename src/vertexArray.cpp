#include "vertexArray.h"

 
void vertexArray::addBuffer(const vertexBuffer& vbo, const vertexLayout& vlb)
{
	vbo.bind();
	const auto& elements = vlb.m_Elements;
	int offset=0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normailzed, vlb.getStride(), (const void*)offset);
		offset += elements[i].count * sizeof(elements[i].type);
	}

}

