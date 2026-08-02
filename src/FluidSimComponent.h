#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Particle.h"
#include "Mesh.h"
#include "Lines.h"
#include "ShaderPipelineComponent.h"

using namespace glm;

class FluidSimComponent {
public:

	bool physicsPlay = false;

	ShaderPipelineComponent shaderPipelineComponent;

	FluidSimComponent();
	~FluidSimComponent();

	float GetParticleDensity() { return particleDensity; };
	void SetParticleDensity(float i_particleDensity) { particleDensity = i_particleDensity; FillInnerCage(); };

	void FillInnerCage();

	// OUTER CAGE FUNCTIONS
	vec3 GetOuterCageSize() { return vec3{ outerCage.scale.x, outerCage.scale.y, outerCage.scale.z }; };
	void ResizeOuterCage(vec3 scale);

	// INNER CAGE FUNCTIONS
	vec3 GetInnerCagePos() { return innerCage.position; };
	vec3 GetInnerCageRot() { return innerCage.rotation; };
	vec3 GetInnerCageSize() { return innerCage.scale; };
	void SetInnerCagePos(vec3 position);
	void SetInnerCageRot(vec3 rotation);
	void ResizeInnerCage(vec3 scale);

	void Draw(Camera& camera);

private:

	float particleDensity = 0.5f;

	const vec3 innerBoundingBoxColor { 0.0f, 1.0f, 1.0f };
	const vec3 outerBoundingBoxColor { 1.0f, 1.0f, 1.0f };

	Lines innerBoundingBox, outerBoundingBox;
	Mesh innerCage{ "models/cage.obj" };
	Mesh outerCage{ "models/cage.obj" };

	Mesh ball{ "models/sphere.obj", vec3(1.0f, 0.3f, 0.3f) };

	std::vector<Mesh*> meshCollection;

	std::vector<Particle> particles;
	std::vector<vec4> particleSSBO;

	float SmoothingKernel(vec3 A, vec3 B);
	vec3 SmoothingKernelGradient(vec3 A, vec3 B);
	float GetDensity(vec3 position);
	vec3 GetPressureForce(vec3 position);
	void SimulateTimeStep(float timeStep);

};