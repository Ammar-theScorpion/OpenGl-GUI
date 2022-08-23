#pragma once
#include<string>
#include"GL/glew.h"
#include"GLFW/glfw3.h"
class texture {
public:
	texture(const std::string& stringPath);
	~texture();

	void bind(unsigned int slot = 0)const;
	void unbind()const;
	void load();
	inline int getWidth()const { return width; }
	inline int getHeight()const { return height; }

private:
	unsigned int m_Renderer;
	std::string stringPath;
	unsigned char* m_LocalBuffer;
	int width, height, m_BPP;
};