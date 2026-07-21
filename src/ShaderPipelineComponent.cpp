#pragma once

#include "ShaderPipelineComponent.h"

ShaderPipelineComponent::ShaderPipelineComponent() {

	defaultShader = new Shader{ "shaders/default.vert", "shaders/default.frag" };
	lineShader = new Shader{ "shaders/line_default.vert", "shaders/line_default.frag" };

}

ShaderPipelineComponent::~ShaderPipelineComponent() {

	defaultShader->Delete();
	lineShader->Delete();

}

void ShaderPipelineComponent::Draw(LiquidSimComponent& liquidSimComponent, Camera& camera) {

	camera.updateMatrix(*defaultShader);
	camera.updateMatrix(*lineShader);

	defaultShaderUniforms(camera);

	liquidSimComponent.cage.Draw(*defaultShader);
	liquidSimComponent.lines.Draw(*lineShader);

}

void ShaderPipelineComponent::defaultShaderUniforms(Camera& camera) {

	defaultShader->Activate();

	int camPosUniformLocation = glGetUniformLocation(defaultShader->ID, "u_camPos");
	glUniform3f(camPosUniformLocation, camera.Position.x, camera.Position.y, camera.Position.z);

}