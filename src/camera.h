#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

enum class cameraDirection
{
	NONE=0,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class camera {
public:
	glm::vec3 cameraPos;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	glm::vec3 worldUp;

	float yaw;
	float pitch;
	float speed;
	float zoom;

	camera(glm::vec3 position);
	void updateCameraPosition(cameraDirection cameraDir, float dt);
	void updateCameraDirection(float dx, float dy);
	void updateCameraZoom(double dy);

	glm::mat4 getViewMatrix();

private:
	void updateCameraVectors();
};