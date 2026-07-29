#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Lines.h"
#include "ShaderPipelineComponent.h"

using namespace glm;

struct Particle {

	vec3 position;
	vec3 velocity;

};

class FluidSimComponent {
public:

	ShaderPipelineComponent shaderPipelineComponent;

	FluidSimComponent();
	~FluidSimComponent();

	vec3 getInnerCageSize() { return vec3 { innerCage.scale.x, innerCage.scale.y, innerCage.scale.z }; };
	vec3 getOuterCageSize() { return vec3 { outerCage.scale.x, outerCage.scale.y, outerCage.scale.z }; }

	void ResizeInnerCage(float width, float length, float height);
	void ResizeOuterCage(float width, float length, float height);

	void Draw(Camera& camera);

private:

	const vec3 innerBoundingBoxColor { 0.0f, 1.0f, 1.0f };
	const vec3 outerBoundingBoxColor { 1.0f, 1.0f, 1.0f };

	Lines innerBoundingBox, outerBoundingBox;
	Mesh innerCage{ "models/cage.obj" };
	Mesh outerCage{ "models/cage.obj" };

	std::vector<Particle> particles;

	void simulateTimeStep(float timeStep);

};