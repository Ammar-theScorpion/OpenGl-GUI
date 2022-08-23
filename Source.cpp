#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include"glm/glm.hpp"
#include"glm/vec2.hpp"
#include"glm/vec3.hpp"
#include"glm/vec4.hpp"
#include"glm/mat4x4.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"src/shader.h"
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "src/io/onKeyEventListener.h"
#include "src/vertexBuffer.h"
#include "src/indexBuffer.h"
#include "src/vertexArray.h"
#include "src/vertexLayoutBuffer.h"
#include"src/texture.h"
#include"src/io/onKeyEventListener.h"
#include"src/camera.h"

void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
void onWindowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
struct vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
};

int main()
{
	camera ca(glm::vec3(0.0f, 0.0f, 3.0f));

	glm::vec3 position(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraDir(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirVec = glm::normalize(position - cameraDir);

	glm::vec3 upVec(0.0f, 1.0f, 0.0f);
	glm::vec3 rightVec = glm::normalize(glm::cross(upVec, cameraDirVec));

	glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirVec, rightVec));

	float vertices[]
	{
   -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indecies[]
	{
		0, 1, 2,
		2, 3, 0
	};

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int frameBufferWidth;
	int frameBufferHeight;
	if (!glfwInit())
		return -1;



	glfwSwapInterval(1);
	GLFWwindow* window = glfwCreateWindow(640, 480, "glow", nullptr, nullptr);
	glfwSetKeyCallback(window, OnKeyEventListener::keyCallBack);
	unsigned int program;
	
	glfwSetFramebufferSizeCallback(window, onWindowResizeCallback);
	//glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	//glViewport(0, 0, frameBufferWidth, frameBufferHeight);
	
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
	}
 
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);


	shader mainShader = shader("src/BasicShader.shader");
 
	mainShader.unifrom4f("u_Color");// uniform are called for a draw call cannot draw two objects with ehis
	// to draw any thing you need a vertex buffer and shader
		// buffer-block of memory in GPU
 
	glm::mat4 translate = glm::mat4(1.0f);
	vertexBuffer vb = vertexBuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);

	// shaders read form GPU buffer and draw it
	// need a way to determine the layout of the buffer
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0); // stride is the size from 1 vertex to another
	//glEnableVertexAttribArray(0);// layout is done, now is time for shader // 0 links vao and vbo

	//indexBuffer ind = indexBuffer(indecies, 6, GL_STATIC_DRAW);

	texture textureImage = texture("src/rr.png");
	textureImage.bind(0);
	mainShader.unifrom1f("u_Texture", 0);
 
 
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3*sizeof(float)));
	 // index of the position attrib
	translate = glm::rotate(translate, glm::radians(45.0f), glm::vec3(1.0, 0, 0));
	translate = glm::rotate(translate, glm::radians(45.0f), glm::vec3(0.0, 1, 0));
	mainShader.unifromMatrix4fv("translate", translate);

	float lastTime = 0.0f;
	float currentFrame = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		double now = glfwGetTime();
		currentFrame = now - lastTime;
		lastTime = now;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime()*glm::radians(55.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		view = ca.getViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		textureImage.bind();
		mainShader.unifrom1f("u_Texture", 0);
		mainShader.unifromMatrix4fv("translate", (projection* view*model ));
		glDrawArrays(GL_TRIANGLES, 0, 36);// vertex shader : where you want the positions to be	
		// fragment shader : determines the color for each pixel
		if (OnKeyEventListener::keyWentDown(GLFW_KEY_W))
			ca.updateCameraPosition(cameraDirection::FORWARD, currentFrame);
		if (OnKeyEventListener::keyWentDown(GLFW_KEY_S))
			ca.updateCameraPosition(cameraDirection::BACKWARD, currentFrame);
		if (OnKeyEventListener::keyWentDown(GLFW_KEY_D))
			ca.updateCameraPosition(cameraDirection::RIGHT, currentFrame);
		if (OnKeyEventListener::keyWentDown(GLFW_KEY_A))
			ca.updateCameraPosition(cameraDirection::LEFT, currentFrame);
		if (OnKeyEventListener::keyWentDown(GLFW_KEY_SPACE))
			ca.updateCameraPosition(cameraDirection::UP, currentFrame);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
}