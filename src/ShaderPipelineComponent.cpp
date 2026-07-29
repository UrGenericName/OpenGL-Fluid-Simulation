#pragma once

#include "ShaderPipelineComponent.h"

using namespace std;
using namespace glm;

ShaderPipelineComponent::ShaderPipelineComponent() {

	meshShader = new Shader{ "shaders/mesh.vert", "shaders/mesh.frag" };
	particleShader = new Shader{ "shaders/particle.vert", "shaders/particle.frag" };
	lineShader = new Shader{ "shaders/line.vert", "shaders/line.frag" };
	generateParticleSSBO();

}

ShaderPipelineComponent::~ShaderPipelineComponent() {

	particleShader->Delete();
	lineShader->Delete();
	deleteParticleSSBO();

}

void ShaderPipelineComponent::Draw_Mesh(Camera& camera, Mesh& mesh) {

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	camera.updateMatrix(*meshShader);
	generateMeshShaderUniforms(camera);

	mesh.Draw(*meshShader);

}

void ShaderPipelineComponent::Draw_Particles(Camera& camera, Mesh& innerCage, Mesh& outerCage, unsigned int particleCount) {

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	camera.updateMatrix(*particleShader);
	generateParticleShaderUniforms(camera, particleCount, outerCage.scale);

	outerCage.Draw(*particleShader);
}

void ShaderPipelineComponent::Draw_BoundingBoxes(Camera& camera, Lines& innerBoundingBox, Lines& outerBoundingBox) {

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	camera.updateMatrix(*lineShader);

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

void ShaderPipelineComponent::generateMeshShaderUniforms(Camera& camera) {

	meshShader->Activate();

	int camPosUniformLocation = glGetUniformLocation(meshShader->ID, "u_camPos");
	glUniform3f(camPosUniformLocation, camera.Position.x, camera.Position.y, camera.Position.z);

}

void ShaderPipelineComponent::generateParticleShaderUniforms(Camera& camera, unsigned int particleCount, vec3 cageSize) {

	particleShader->Activate();

	int camPosUniformLocation = glGetUniformLocation(particleShader->ID, "u_camPos");
	glUniform3f(camPosUniformLocation, camera.Position.x, camera.Position.y, camera.Position.z);

	int particleCountUniformLocation = glGetUniformLocation(particleShader->ID, "u_particleCount");
	glUniform1ui(particleCountUniformLocation, particleCount);

	int cageSizeUniformLocation = glGetUniformLocation(particleShader->ID, "u_cageSize");
	glUniform3f(cageSizeUniformLocation, cageSize.x, cageSize.y, cageSize.z);

}