#include <stdio.h>
#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "objloader.hpp"

Mesh::Mesh(std::string meshFile, GLuint shader)
{
	m_shader = shader;
	Load(meshFile);

	m_modelMatrixID = glGetUniformLocation(m_shader, "MM");
	m_itMatrixID = glGetUniformLocation(m_shader, "IT");
}

Mesh::~Mesh()
{
}

void Mesh::Clear()
{
	m_vertices.clear();
	m_uvs.clear();
	m_normals.clear();

	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_vuv);
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::DrawMesh()
{
	UpdateMatrix();
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_matrix[0][0]);

	glm::mat3 invTranspose = 
		glm::transpose(
			glm::inverse(
				glm::mat3(m_matrix)));
	glUniformMatrix3fv(m_itMatrixID, 1, GL_FALSE, &invTranspose[0][0]);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}

void Mesh::Load(std::string meshFile)
{
	loadOBJ(
		"bunny.obj", 
		m_vertices, 
		m_uvs, 
		m_normals);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(glm::vec3) * m_vertices.size(),
		&m_vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &m_vuv);
	glBindBuffer(GL_ARRAY_BUFFER, m_vuv);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(glm::vec2) * m_uvs.size(),
		&m_uvs[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &m_vno);
	glBindBuffer(GL_ARRAY_BUFFER, m_vno);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(glm::vec3) * m_normals.size(),
		&m_normals[0],
		GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_vuv);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_vno);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}