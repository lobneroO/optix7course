
#include "Camera.h"

#include "GLFW/glfw3.h"

#include "gdt/math/Quaternion.h"

Camera::Camera(const vec3f& eye /* = vec3f(0.f, 0.f, 0.f)*/, 
	const vec3f& at /* = vec3f(0.f, 0.f, -1.f)*/, 
	const vec3f& up /* = vec3f(0.f, 1.f, 0.f)*/,
	const float& cosFovy /* = 0.66f*/,
	const uint32_t& width /* = 1024 */, const uint32_t height /* = 768 */)
{
	Eye = eye;
	At = at;
	Up = up;

	InitialEye = eye;
	InitialAt = at;
	InitialUp = up;

	CosFovy = cosFovy;
	Width = width;
	Height = height;

	std::fill_n(KeyStatus, 256, 0);
	std::fill_n(MouseStatus, 8, 0);
}

Camera::~Camera()
{

}

void Camera::Tick(const float& deltaTime_seconds)
{
	Move(deltaTime_seconds);
}

void Camera::Move(const float& deltaTime_seconds)
{
	vec3f forward = normalize(At - Eye);
	vec3f right = cross(forward, Up);

	if (KeyStatus[GLFW_KEY_A])
	{
		Eye -= Speed * deltaTime_seconds * right;
	}
	if (KeyStatus[GLFW_KEY_D])
	{
		Eye += Speed * deltaTime_seconds * right;
	}
	if (KeyStatus[GLFW_KEY_W])
	{
		Eye += Speed * deltaTime_seconds * forward;
	}
	if (KeyStatus[GLFW_KEY_S])
	{
		Eye -= Speed * deltaTime_seconds * forward;
	}
	if (KeyStatus[GLFW_KEY_E])
	{
		Eye += Speed * deltaTime_seconds * Up;
	}
	if (KeyStatus[GLFW_KEY_Q])
	{
		Eye -= Speed * deltaTime_seconds * Up;
	}

	if (KeyStatus[GLFW_KEY_0])
	{
		Eye = vec3f(0.f, 0.f, 0.f);
	}
	if (KeyStatus[GLFW_KEY_9])
	{
		Eye = InitialEye;
		At = InitialAt;
		Up = InitialUp;
	}

	// mouse action
	if (MouseStatus[GLFW_MOUSE_BUTTON_LEFT])
	{
		vec2f way = CurrentMousePos_Normalized - LastMousePos_Normalized;
		float distance = sqrtf(way.x * way.x + way.y * way.y);
		float angle = acos(distance);

		std::string str = "way:("
			+ std::to_string(way.x) + ","
			+ std::to_string(way.y) + ","
			+ "); ";
		
		str += "old dir:("
			+ std::to_string(forward.x) + ","
			+ std::to_string(forward.y) + ","
			+ std::to_string(forward.z) + ","
			+ "); ";
		str += "angle:" + std::to_string(angle) + "; ";

		Quaternion3f quat = Quaternion3f::rotate(Up, angle);

		forward = quat * forward;

		str += "new dir:("
			+ std::to_string(forward.x) + ","
			+ std::to_string(forward.y) + ","
			+ std::to_string(forward.z) + ","
			+ "); ";

		std::cout << str << std::endl;

		At = Eye + forward;
	}
}

void Camera::SetEye(const vec3f& eye)
{
	Eye = eye;
}

vec3f Camera::GetEye() const
{
	return Eye;
}

void Camera::SetAt(const vec3f& at)
{
	At = at;
}

vec3f Camera::GetAt() const
{
	return At;
}

void Camera::SetUp(const vec3f& up)
{
	Up = up;
}

vec3f Camera::GetUp() const
{
	return Up;
}

void Camera::SetCosFovy(const float& cosFovy)
{
	CosFovy = cosFovy;
}

float Camera::GetCosFovy() const
{
	return CosFovy;
}

float Camera::GetSpeed() const
{
	return Speed;
}

void Camera::KeyDown(const int32_t& key)
{
	KeyStatus[key] = 1;
}

void Camera::KeyUp(const int32_t& key)
{
	KeyStatus[key] = 0;
}

void Camera::SetMousePos(const vec2f& NormalizedMousePos)
{
	LastMousePos_Normalized = CurrentMousePos_Normalized;
	CurrentMousePos_Normalized = NormalizedMousePos;
}

void Camera::MouseDown(const int32_t& button)
{
	MouseStatus[button] = 1;
}

void Camera::MousUp(const int32_t& button)
{
	MouseStatus[button] = 0;
}

CameraOptix Camera::GetOptixCamera() const
{
	CameraOptix cam;
	cam.Position = Eye;
	cam.LookingDirection = normalize(At - Eye);
	cam.CosFovy = CosFovy;
	const float aspectRatio = Width / Height;
	cam.Horizontal = CosFovy * aspectRatio * normalize(cross(cam.LookingDirection, Up));
	cam.Vertical = CosFovy * normalize(cross(cam.Horizontal, cam.LookingDirection));

	return cam;
}