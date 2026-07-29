#pragma once

#include "Mesh.h"
#include "Lines.h"
#include "Camera.h"

#define MAX_PARTICLES 4096

class ShaderPipelineComponent {
public:

	Shader* defaultShader;
	Shader* lineShader;

	ShaderPipelineComponent();
	~ShaderPipelineComponent();

	void Draw(Camera& camera, Mesh& innerCage, Mesh& outerCage, Lines& innerBoundingBox, Lines& outerBoundingBox, unsigned int particleCount);

	void generateParticleSSBO();
	void updateParticleSSBO(std::vector<glm::vec4> particles);
	void deleteParticleSSBO();

private:

	GLuint particleSSBO;

	void generateDefaultShaderUniforms(Camera& camera, unsigned int particleCount, glm::vec3 cageSize);

};