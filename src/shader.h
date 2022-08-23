#pragma once
#include<string>
#include<sstream>
#include<fstream>
#include"GL/glew.h"
#include"glm/glm.hpp"
struct shaderSourceString
{
	std::string vertexShader;
	std::string fragmentShader;
};

class shader {
public:
	shader(const std::string& stringPath);
	~shader();
	shaderSourceString parseShader(const std::string& stringPath);
	int getUnifrom4fLocation(const char* stringUniform);
	void unifrom4f(const char* stringName);
	void unifromMatrix4fv(const char* stringName, const glm::mat4 mat);
	void unifrom1f(const char* stringName, int val);

	void bindProgram();
	void unbindProgram();

private:
	unsigned int m_Renderer;
private:
	unsigned int compileShader(int type, const std::string& stringType);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
};