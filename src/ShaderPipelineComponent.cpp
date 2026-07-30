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

void ShaderPipelineComponent::Draw_Particles(Camera& camera, Mesh& innerCage, Mesh& outerCage, unsigned int particleCount) {

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	camera.updateMatrix(*particleShader);
	generateParticleShaderUniforms(camera, particleCount, outerCage.scale);

	outerCage.Draw(*particleShader);
}

void ShaderPipelineComponent::Draw_BoundingBoxes(Camera& camera, Lines& innerBoundingBox, Lines& outerBoundingBox) {

	camera.updateMatrix(*lineShader);

	innerBoundingBox.Draw(*lineShader);
	outerBoundingBox.Draw(*lineShader);

}

void ShaderPipelineComponent::Draw_Mesh(Camera& camera, Mesh& mesh) {

	camera.updateMatrix(*meshShader);
	generateMeshShaderUniforms(camera);

	mesh.Draw(*meshShader);

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

void ShaderPipelineComponent::generateParticleShaderUniforms(Camera& camera, unsigned int particleCount, vec3 cageSize) {

	particleShader->Activate();

	GLuint u_camPosUniformLoc = glGetUniformLocation(particleShader->ID, "u_camPos");
	glUniform3f(u_camPosUniformLoc, camera.Position.x, camera.Position.y, camera.Position.z);

	GLuint u_particleCountUniformLoc = glGetUniformLocation(particleShader->ID, "u_particleCount");
	glUniform1ui(u_particleCountUniformLoc, particleCount);

	GLuint u_particleRadiusUniformLoc = glGetUniformLocation(particleShader->ID, "u_particleRadius");
	glUniform1f(u_particleRadiusUniformLoc, particleRenderRadius);

	GLuint u_cageSizeUniformLoc = glGetUniformLocation(particleShader->ID, "u_cageSize");
	glUniform3f(u_cageSizeUniformLoc, cageSize.x, cageSize.y, cageSize.z);

}

void ShaderPipelineComponent::generateMeshShaderUniforms(Camera& camera) {

	meshShader->Activate();

}