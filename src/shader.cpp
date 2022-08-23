#include"shader.h"
#include<iostream>
shader::shader(const std::string& stringPath)
{
	shaderSourceString shaderSourceString = parseShader(stringPath);
	m_Renderer = createShader(shaderSourceString.vertexShader, shaderSourceString.fragmentShader);
	glUseProgram(m_Renderer);
}
shaderSourceString shader::parseShader(const std::string& stringPath)
{
	enum class shaderType {
		NONE = -1, VERTEX = 0, FRAGMENT
	}type;
	std::stringstream ss[2];
	std::ifstream file;
	std::string line;
	file.open(stringPath);
	while (std::getline(file, line))
	{
		if (line.find("vertex shader") != std::string::npos)
			type = shaderType::VERTEX;

		else if (line.find("fragment shader") != std::string::npos)
			type = shaderType::FRAGMENT;
		else
			ss[(int)type] << line << "\n";
	}
	return { ss[0].str(), ss[1].str() };
	
}

 

void shader::unifrom4f(const char* stringName)
{
	glUniform4f(getUnifrom4fLocation(stringName), 1.0f, 0.6f, 0.1f, 1.0f);
}

void shader::unifromMatrix4fv(const char* stringName, const glm::mat4 mat)
{
	glUniformMatrix4fv(getUnifrom4fLocation(stringName), 1, GL_FALSE, &mat[0][0]);
}
void shader::unifrom1f(const char* stringName, int val)
{
	glUniform1f(getUnifrom4fLocation(stringName), val);
}

int shader::getUnifrom4fLocation(const char* stringUniform)
{
	return glGetUniformLocation(m_Renderer, stringUniform);
}

void shader::bindProgram()
{
	glUseProgram(m_Renderer);
}

void shader::unbindProgram()
{
	glUseProgram(0);

}

unsigned int shader::compileShader(int type, const std::string& stringType)
{
	int src = glCreateShader(type);
	const char* stringSrc = stringType.c_str();

	glShaderSource(src, 1, &stringSrc, nullptr);
	glCompileShader(src);

	int result;
	glGetShaderiv(src, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(src, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(src, length, &length, message);
		std::cout << "Error while compiling " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader " << message;
		glDeleteShader(src);
		return 0;
	}
	return src;
}

unsigned int shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	std::cout << vertexShader;
	std::cout << fragmentShader;

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
shader::~shader()
{
	glDeleteProgram(m_Renderer);
	//glDeleteShader will not delete the shader unless its not bound to any program.
}