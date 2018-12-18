#pragma once
#include <glm/glm.hpp>

class Transform
{
public:
	glm::mat4 m_matrix;
	glm::mat4 m_rotationMatrix;
	glm::mat4 m_translateMatrix;

	Transform();
	~Transform();
	void Translate(glm::vec3 p);
	void Rotate(float a, glm::vec3 axis);
	void UpdateMatrix();
	glm::vec3 Forward();
};

