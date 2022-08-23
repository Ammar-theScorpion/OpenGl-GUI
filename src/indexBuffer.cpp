#include "indexBuffer.h"

indexBuffer::indexBuffer(const void* vertices, int count, int type)
{
	glGenBuffers(1, &m_Renderer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer);//select the generated buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), vertices, type);// fill the buffer with the data GL_STATIC_DRAW the data wont be modified but renderd every time.
}

indexBuffer::~indexBuffer()
{
	glDeleteBuffers(1, &m_Renderer);
}

void indexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer);
}

void indexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
