#ifndef UTILS_H
#define UTILS_H

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

glm::mat4 GetBillboardModelMatrix(const glm::vec3& center, const glm::vec3& eye) {
	glm::vec3 forward = glm::normalize(center - eye);  // Forward direction
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);                   // Up direction (adjust if needed)
	glm::vec3 right = glm::normalize(glm::cross(up, forward));    // Right vector
	up = glm::cross(forward, right);                              // Recalculate up to ensure orthogonality

	// Construct rotation matrix
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0] = glm::vec4(right, 0.0f);
	rotation[1] = glm::vec4(up, 0.0f);
	rotation[2] = glm::vec4(-forward, 0.0f);  // Negate forward for right-handed system

	// Apply translation to position the billboard correctly
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), eye);

	// Final model matrix
	glm::mat4 model = translation * rotation;

	return model;
}


#endif // !UTILS_H
