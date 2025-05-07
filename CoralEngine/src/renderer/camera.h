#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

enum class ProjectionType
{
	Perspective,
	Orthogonal
};

typedef struct
{
	ProjectionType Projection;
	glm::vec3 Position;
	glm::vec3 Rotation;

	float Fov;

	float SensitivityX;
	float SensitivityY;

	float MovementSpeed;

	float NearPlane;
	float FarPlane;


	glm::mat4x4 m_ProjectionMatrix;
	glm::mat4x4 m_ViewMatrix;

} CameraInfo;

void camera_update(CameraInfo* rpCamera);

#endif // !CAMERA_H


