#include <stdio.h>
#include <stdlib.h>
#include <GLEW/GL/glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include "shader.hpp"
#include "Scene.h"

Scene::Scene()
{
	m_shader = LoadShaders(
		"VertexShader.glsl",
		"FragmentShader.glsl");

	m_viewMatrixID = glGetUniformLocation(m_shader, "VM");
	m_projectionMatrixID = glGetUniformLocation(m_shader, "PM");
	m_lightAmountID = glGetUniformLocation(m_shader, "LightAmount");
	m_lightDirID = glGetUniformLocation(m_shader, "LightDir");
	m_wsCameraDirID = glGetUniformLocation(m_shader, "WorldSpaceCameraDirection");
	m_specularAmountID = glGetUniformLocation(m_shader, "SpecularAmount");
	m_specularGlossID = glGetUniformLocation(m_shader, "SpecularGloss");

	m_projectionMatrix = glm::perspective(
		glm::radians(45.0f),
		4.0f / 3.0f,
		0.1f,
		100.0f);

	m_cameraPosition = glm::vec3(4, 3, 3);
	m_cameraTarget = glm::vec3(0, 0, 0);
	m_viewMatrix = glm::lookAt(
		m_cameraPosition,
		m_cameraTarget,
		glm::vec3(0, 1, 0)
	);

	m_light.Rotate(
		glm::radians(-65.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}

Scene::~Scene()
{
}

void Scene::AddMesh(std::string meshFile)
{
	Mesh m(meshFile, m_shader);
	m_meshes.push_back(m);
}

void Scene::Clear()
{
	for (int i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i].Clear();
	}
	m_meshes.clear();
	glDeleteProgram(m_shader);
}

void Scene::Draw(float in)
{
	glUseProgram(m_shader);
	glUniformMatrix4fv(
		m_viewMatrixID, 
		1, 
		GL_FALSE, 
		&m_viewMatrix[0][0]);
	glUniformMatrix4fv(
		m_projectionMatrixID, 
		1, 
		GL_FALSE, 
		&m_projectionMatrix[0][0]);

	glm::vec3 camDir = glm::normalize(m_cameraPosition - m_cameraTarget);
	glUniform3f(
		m_wsCameraDirID,
		camDir.x,
		camDir.y,
		camDir.z);
	
	glUniform1f(m_specularAmountID, m_light.m_specularAmount);
	glUniform1f(m_specularGlossID, m_light.m_specularGloss);
	glUniform1f(m_lightAmountID, m_light.m_lightAmount);
	m_light.Rotate(in, glm::vec3(0,1,0));
	m_light.UpdateMatrix();
	glm::vec3 d = m_light.Forward();
	glUniform3f(m_lightDirID, d.x, d.y, d.z);
	;
	

	for (int i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i].DrawMesh();
	}
}
