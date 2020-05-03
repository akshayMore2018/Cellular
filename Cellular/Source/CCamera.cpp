#include "CCamera.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CCamera::CCamera()
{
	Position		= glm::vec3(0.0f, 0.0f, 3.0f);
	ForwardVector	= glm::vec3(0.0f, 0.0f, -1.0f);
	UpVector		= glm::vec3(0.0f, 1.0f, 0.0f);
	Velocity		= glm::vec3(0.0f, 0.0f, 0.0f);
	firstMouse		= true;

	yaw				= -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch			= 0.0f;
	lastX			= 800.0f / 2.0;
	lastY			= 600.0 / 2.0;
	fov				= 45.0f;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CCamera::Update(float DeltaTime)
{
	Position += Velocity * DeltaTime;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CCamera::Events(GLFWwindow *mWindow)
{
	double xpos = 0.0;
	double ypos = 0.0;
	glfwGetCursorPos(mWindow, &xpos, &ypos);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; 
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x			= cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y			= sin(glm::radians(pitch));
	front.z			= sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	ForwardVector	= glm::normalize(front);



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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

glm::vec3 CCamera::GetPosition()const
{
	return Position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

glm::vec3 CCamera::GetForwardVector() const
{
	return ForwardVector;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

glm::vec3 CCamera::GetUpVector() const
{
	return UpVector;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////