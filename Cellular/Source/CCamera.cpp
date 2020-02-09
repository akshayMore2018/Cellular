#include "CCamera.h"

CCamera::CCamera()
{
	Position		= glm::vec3(0.0f, 0.0f, 3.0f);
	ForwardVector	= glm::vec3(0.0f, 0.0f, -1.0f);
	UpVector		= glm::vec3(0.0f, 1.0f, 0.0f);
	Velocity		= glm::vec3(0.0f, 0.0f, 0.0f);
}

void CCamera::SetPosition(const glm::vec3 & Pos)
{
	Position = Pos;
}

void CCamera::Update(float DeltaTime)
{
	Position += Velocity * DeltaTime;
}

void CCamera::Events(GLFWwindow *mWindow)
{
	glm::vec3 Direction = glm::vec3(0.0f,0.0f,0.0f);
	float Speed = 0.0f;
	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		Direction	= ForwardVector;
		Speed		= 2.5f;
	}
	if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		Direction	= -ForwardVector;
		Speed		= 2.5f;
	}
	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		Direction	= -glm::normalize(glm::cross(ForwardVector, UpVector));
		Speed		= 2.5f;
	}
	if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		Direction	= glm::normalize(glm::cross(ForwardVector, UpVector));
		Speed		= 2.5f;
	}

	Velocity = Direction * Speed;
}

glm::vec3 CCamera::GetPosition()const
{
	return Position;
}

glm::vec3 CCamera::GetForardVector() const
{
	return ForwardVector;
}

glm::vec3 CCamera::GetUpVector() const
{
	return UpVector;
}
