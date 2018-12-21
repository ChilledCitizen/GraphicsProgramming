#pragma once

#include <vector>
#include <string>
#include <GLEW/GL/glew.h>
#include <glm/glm.hpp>
#include "Transform.h"

class Mesh : public Transform
{
public:	
	Mesh(const char* meshFile,const char* textureFile, GLuint shader);
	~Mesh();
	void Clear();
	void DrawMesh();
	GLuint m_shader;

private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_normals;

	GLuint m_vbo;
	GLuint m_vuv;
	GLuint m_vno;
	GLuint m_vao;
	GLuint m_modelMatrixID;
	GLuint m_itMatrixID;
	
	GLuint m_mainTexID;
	GLuint m_mainTex;

	void Load(const char * meshFile, const char * texture);
};