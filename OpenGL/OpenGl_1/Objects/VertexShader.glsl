#version 330 core

layout(location=0) in vec3 vertexPosition_modelspace;
layout(location=1) in vec2 uv;
layout(location=2) in vec3 vertexNormal;

out vec3 fragmentColor;
out vec2 UV;

uniform mat4 MM;
uniform mat4 VM;
uniform mat4 PM;
uniform mat3 IT;
uniform vec3 WorldSpaceCameraDirection;
uniform vec3 LightDir;
uniform float LightAmount;
uniform float SpecularAmount;
uniform float SpecularGloss;

void main()
{
	vec3 normalDirection = normalize(IT * vertexNormal);
	gl_Position = PM * VM * MM * vec4(vertexPosition_modelspace, 1);

	float nd = max(0.0, dot(normalDirection, LightDir));
	vec3 r = reflect(-LightDir, normalDirection);
	float rv = max(0.0, dot(r, WorldSpaceCameraDirection));
	float s = 0.0;
	if(dot(normalDirection, LightDir) > 0.0)
	{
		s = pow(rv, SpecularGloss);
	}

	fragmentColor = vec3(1.0,1.0,1.0);// * nd * LightAmount;
	UV = uv;
}