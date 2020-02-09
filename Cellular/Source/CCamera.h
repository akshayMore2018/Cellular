#pragma once
#include "CEngine.h"

class CCamera
{
public:

	CCamera();


	void SetPosition(const glm::vec3& Pos);
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

};