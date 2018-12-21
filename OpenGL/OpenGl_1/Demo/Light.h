#pragma once
#include "Transform.h"

class Light : public Transform
{
public:
	Light();
	~Light();
	float m_lightAmount = 1.0f;
	float m_specularAmount = 1.0f;
	float m_specularGloss = 50.0f;
};

