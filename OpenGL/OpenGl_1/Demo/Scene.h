#pragma once
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Light.h"

class Scene
{
public:
	Scene();
	~Scene();
	void AddMesh(std::string meshFile);
	void Clear();
	void Draw(float in);

private:
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	GLuint m_viewMatrixID;
	GLuint m_projectionMatrixID;
	std::vector<Mesh> m_meshes;
	GLuint m_shader;
	Light m_light;
	GLuint m_lightAmountID;
	GLuint m_lightDirID;
	GLuint m_wsCameraDirID;
	GLuint m_specularAmountID;
	GLuint m_specularGlossID;
	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraTarget;
	float tmp[20];
	int index = 0;
};

