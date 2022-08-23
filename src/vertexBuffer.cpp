#include "vertexBuffer.h"

vertexBuffer::vertexBuffer(const void* vertices, int size, int type)
{
	glGenBuffers(1, &m_Renderer);
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);//select the generated buffer
	glBufferData(GL_ARRAY_BUFFER, size, vertices, type);// fill the buffer with the data GL_STATIC_DRAW the data wont be modified but renderd every time.
}

vertexBuffer::~vertexBuffer()
{
	glDeleteBuffers(1, &m_Renderer);
}

void vertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);
}

void vertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
