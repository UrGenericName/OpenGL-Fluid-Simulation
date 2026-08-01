#pragma once

#include "Mesh.h"
#include "Lines.h"
#include "Camera.h"

#define MAX_PARTICLES 4096

class ShaderPipelineComponent {
public:

	float particleRenderRadius = 1.0f / 32.0f;

	Shader* meshShader;
	Shader* particleShader;
	Shader* lineShader;

	ShaderPipelineComponent();
	~ShaderPipelineComponent();

	void Draw_Particles(Camera& camera, Mesh& innerCage, Mesh& outerCage, unsigned int particleCount);
	void Draw_BoundingBoxes(Camera& camera, Lines& innerBoundingBox, Lines& outerBoundingBox);
	void Draw_Meshes(Camera& camera, std::vector<Mesh*>& meshCollection);

	void generateParticleSSBO();
	void updateParticleSSBO(std::vector<glm::vec4> particles);
	void deleteParticleSSBO();

private:

	GLuint particleSSBO;
	
	void generateParticleShaderUniforms(Camera& camera, unsigned int particleCount, glm::vec3 cageSize);
	void generateMeshShaderUniforms(Camera& camera);

};