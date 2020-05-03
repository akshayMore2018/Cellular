#include "CCamera.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CCamera::CCamera()
{
	Position		= glm::vec3(0.0f, 0.0f, 3.0f);
	Velocity		= glm::vec3(0.0f, 0.0f, 0.0f);
	WorldUp			= glm::vec3(0.0f, 1.0f, 0.0f);

	firstMouse		= true;

	yaw				= -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch			= 0.0f;
	lastX			= SCREEN_WIDTH / 2.0;
	lastY			= SCREEN_HEIGHT / 2.0;
	fov				= 45.0f;
	Speed			= 2.5f;
	
	UpdateCameraVectors();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CCamera::Update(float DeltaTime)
{
	Position += Velocity * DeltaTime;
	//if don't do this the camera acts wierd.
	Position.y = 0.0f;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CCamera::Events(GLFWwindow *mWindow)
{
	
	if (glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		double xpos = 0.0;
		double ypos = 0.0;
		glfwGetCursorPos(mWindow, &xpos, &ypos);

		bool CursorInBounds = (xpos > 0 && xpos < SCREEN_WIDTH && ypos > 0 && ypos < SCREEN_HEIGHT);
		
		if (CursorInBounds)
		{
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

			UpdateCameraVectors();
			
		}
		else
		{
			firstMouse = true;
		}
	}
	else
	{
		firstMouse = true;
	}

	glm::vec3 Direction = glm::vec3(0.0f,0.0f,0.0f);
	float MovementSpeed = 0.0f;
	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		Direction	= ForwardVector;
		MovementSpeed = Speed;
	}
	if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		Direction		= -ForwardVector;
		MovementSpeed	= Speed;
	}
	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		Direction		= -RightVector;
		MovementSpeed	= Speed;
	}
	if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		Direction		= RightVector;
		MovementSpeed	= Speed;
	}

	Velocity = Direction * Speed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CCamera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	ForwardVector	= glm::normalize(front);
	RightVector		= glm::normalize(glm::cross(ForwardVector, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	UpVector		= glm::normalize(glm::cross(RightVector, ForwardVector));

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