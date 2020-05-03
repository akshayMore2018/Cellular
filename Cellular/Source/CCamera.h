#pragma once
#include "CEngine.h"

class CCamera
{
public:

	CCamera();
	void Update(float DeltaTime);
	void Events(GLFWwindow *mWindow);

	//Getters
	glm::vec3 GetPosition()const;
	glm::vec3 GetForardVector()const;
	glm::vec3 GetUpVector()const;


private:

	glm::vec3 Position;
	glm::vec3 ForwardVector;
	glm::vec3 UpVector;
	glm::vec3 Velocity;

	bool firstMouse;
	float yaw	;	
	float pitch ;
	float lastX ; 
	float lastY ;
	float fov	;

};