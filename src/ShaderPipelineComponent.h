#pragma once

#include "LiquidSimComponent.h"
#include "Camera.h"

class ShaderPipelineComponent {
public:

	Shader* defaultShader;
	Shader* lineShader;

	ShaderPipelineComponent();
	~ShaderPipelineComponent();

	void Draw(LiquidSimComponent& liquidSimComponent, Camera& camera);

private:

	void defaultShaderUniforms(Camera& camera);

};