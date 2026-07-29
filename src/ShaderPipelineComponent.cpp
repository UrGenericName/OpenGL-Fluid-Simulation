#pragma once

#include "ShaderPipelineComponent.h"

using namespace std;
using namespace glm;

ShaderPipelineComponent::ShaderPipelineComponent() {

	defaultShader = new Shader{ "shaders/default.vert", "shaders/default.frag" };
	lineShader = new Shader{ "shaders/line_default.vert", "shaders/line_default.frag" };
	generateParticleSSBO();

}

ShaderPipelineComponent::~ShaderPipelineComponent() {

	defaultShader->Delete();
	lineShader->Delete();
	deleteParticleSSBO();

}

void ShaderPipelineComponent::Draw(Camera& camera, Mesh& innerCage, Mesh& outerCage, Lines& innerBoundingBox, Lines& outerBoundingBox, unsigned int particleCount) {

	camera.updateMatrix(*defaultShader);
	camera.updateMatrix(*lineShader);

	generateDefaultShaderUniforms(camera, particleCount, outerCage.scale);

	outerCage.Draw(*defaultShader);
	innerBoundingBox.Draw(*lineShader);
	outerBoundingBox.Draw(*lineShader);

}

void ShaderPipelineComponent::generateParticleSSBO() {

	glGenBuffers(1, &particleSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleSSBO);

	glBufferData(
		GL_SHADER_STORAGE_BUFFER,
		MAX_PARTICLES * sizeof(vec4),
		nullptr,
		GL_STATIC_DRAW
	);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particleSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

}

void ShaderPipelineComponent::updateParticleSSBO(vector<vec4> particles) {

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particleSSBO);

	glBufferSubData(
		GL_SHADER_STORAGE_BUFFER,
		0,
		particles.size() * sizeof(particles[0]),
		particles.data()
	);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

}

void ShaderPipelineComponent::deleteParticleSSBO() {

	glDeleteBuffers(1, &particleSSBO);

}

void ShaderPipelineComponent::generateDefaultShaderUniforms(Camera& camera, unsigned int particleCount, vec3 cageSize) {

	defaultShader->Activate();

	int camPosUniformLocation = glGetUniformLocation(defaultShader->ID, "u_camPos");
	glUniform3f(camPosUniformLocation, camera.Position.x, camera.Position.y, camera.Position.z);

	int particleCountUniformLocation = glGetUniformLocation(defaultShader->ID, "u_particleCount");
	glUniform1ui(particleCountUniformLocation, particleCount);

	int cageSizeUniformLocation = glGetUniformLocation(defaultShader->ID, "u_cageSize");
	glUniform3f(cageSizeUniformLocation, cageSize.x, cageSize.y, cageSize.z);

}