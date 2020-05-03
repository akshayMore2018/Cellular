#pragma once
#include "CEngine.h"

class CCamera
{
public:

	CCamera();
	void Update(float DeltaTime);
	void Events(GLFWwindow *mWindow);
	void UpdateCameraVectors();

	//Getters
	glm::vec3 GetPosition()const;
	glm::vec3 GetForwardVector()const;
	glm::vec3 GetUpVector()const;


private:

	glm::vec3 Position;
	glm::vec3 ForwardVector;
	glm::vec3 UpVector;
	glm::vec3 RightVector;
	glm::vec3 WorldUp;
	glm::vec3 Velocity;

	bool firstMouse;
	float yaw	;	
	float pitch ;
	float lastX ; 
	float lastY ;
	float fov	;
	float Speed;

};