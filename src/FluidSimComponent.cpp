#pragma once

#include "FluidSimComponent.h"

using namespace glm;

FluidSimComponent::FluidSimComponent() {

	innerBoundingBox.tint = innerBoundingBoxColor;
	outerBoundingBox.tint = outerBoundingBoxColor;

	ResizeInnerCage(vec3{ 1.0f, 1.0f, 1.0f });
	ResizeOuterCage(vec3{ 16.0f, 16.0f, 16.0f });

}

FluidSimComponent::~FluidSimComponent() {}

void FluidSimComponent::SetInnerCagePos(vec3 position) {

	innerCage.position = position;

	innerBoundingBox.generateFromBoundingBox(innerCage);
	innerBoundingBox.updateBuffers();

	FillInnerCage();

}


void FluidSimComponent::SetInnerCageRot(vec3 rotation) {

	innerCage.rotation = rotation;

	innerBoundingBox.generateFromBoundingBox(innerCage);
	innerBoundingBox.updateBuffers();

	FillInnerCage();

}

void FluidSimComponent::ResizeInnerCage(vec3 scale) {

	innerCage.scale = scale;

	innerBoundingBox.generateFromBoundingBox(innerCage);
	innerBoundingBox.updateBuffers();

	FillInnerCage();

}

void FluidSimComponent::ResizeOuterCage(vec3 scale) {

	outerCage.scale = scale;

	outerBoundingBox.generateFromBoundingBox(outerCage);
	outerBoundingBox.updateBuffers();

}

void FluidSimComponent::FillInnerCage() {

	vec3 minBounds = { -0.5f, -0.5f, -0.5f };
	vec3 maxBounds = { 0.5f, 0.5f, 0.5f };

	// FILL VECTOR
	particles.clear();
	for (float x = minBounds.x; x <= maxBounds.x; x += (particleDensity / innerCage.scale.x) ) {
		for (float y = minBounds.y; y <= maxBounds.y; y += (particleDensity / innerCage.scale.y) ) {
			for (float z = minBounds.z; z <= maxBounds.z; z += (particleDensity / innerCage.scale.z) ) {

				Particle temp{ vec3{x, y, z }, vec3{0.0f} };
				temp.position = vec3(innerCage.getModelMatrix() * vec4(temp.position, 1.0f));
				particles.push_back(temp);

			}
		}
	}

}

void FluidSimComponent::Draw(Camera& camera) {

	SimulateTimeStep(0.001f);

	// CREATE SSBO POS VECTOR
	vector<vec4> particlePosSSBO;

	for (const Particle& p : particles) {
		particlePosSSBO.push_back(vec4{ p.position, 1.0f });
	}

	shaderPipelineComponent.updateParticleSSBO(particlePosSSBO);

	shaderPipelineComponent.Draw(camera, innerCage, outerCage, innerBoundingBox, outerBoundingBox, particles.size());

}

void FluidSimComponent::SimulateTimeStep(float timeStep) {

	for (Particle& particle : particles) {

		particle.velocity += vec3(0.0f, 0.0f, -9.8 * 0.05f);

		vec3 newPosition = particle.position + particle.velocity * timeStep;

		vec3 minBounds = { -outerCage.scale.x / 2.0f, -outerCage.scale.y / 2.0f, -outerCage.scale.z / 2.0f };
		vec3 maxBounds = { outerCage.scale.x / 2.0f, outerCage.scale.y / 2.0f, outerCage.scale.z / 2.0f };

		if (!(minBounds.x < newPosition.x && maxBounds.x > newPosition.x)) particle.velocity *= -1.0f;
		if (!(minBounds.y < newPosition.y && maxBounds.y > newPosition.y)) particle.velocity *= -1.0f;
		if (!(minBounds.z < newPosition.z && maxBounds.z > newPosition.z)) particle.velocity *= -1.0f;

		particle.position += particle.velocity * timeStep;

	}

}