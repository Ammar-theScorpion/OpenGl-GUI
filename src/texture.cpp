#include "texture.h"
#include"stb_image/stb_image.h"
texture::texture(const std::string& stringPath):
	m_Renderer(0), stringPath(stringPath), width(0), height(0),m_LocalBuffer(nullptr), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(stringPath.c_str(), &width, &height, &m_BPP, 4);

	glGenTextures(1, &m_Renderer);
	glBindTexture(GL_TEXTURE_2D, m_Renderer);
	load();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void texture::load()
{

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//s is x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//t is y
}
texture::~texture()
{

}

void texture::bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_Renderer);

}

void texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);

}

