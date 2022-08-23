#pragma once
#include<vector>
#include"GL/glew.h"
struct layoutElements {
	int type;
	int count;
	unsigned char normailzed;
};
class vertexLayout {
private:
	int m_Stride;
public:
	vertexLayout()
		:m_Stride(0) {}
	std::vector< layoutElements > m_Elements;

	template<typename>
	void push(int count) 
	{
		static_assert(false);
	}

	template<>
	void push<float>(int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += 4 * count;
	}

	template<>
	void push<unsigned int>(int count)
	{
		m_Elements.push_back({GL_UNSIGNED_INT, count, GL_TRUE});
		m_Stride += sizeof(GL_UNSIGNED_INT) * count;

	}

	inline int getStride() const{ return m_Stride; }
};