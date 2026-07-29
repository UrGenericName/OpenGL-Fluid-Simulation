#pragma once

#include "FluidSimComponent.h"

using namespace glm;

FluidSimComponent::FluidSimComponent() {

	innerBoundingBox.tint = innerBoundingBoxColor;
	outerBoundingBox.tint = outerBoundingBoxColor;

	ResizeInnerCage(1.0f, 1.0f, 1.0f);
	ResizeOuterCage(2.0f, 2.0f, 2.0f);

}

FluidSimComponent::~FluidSimComponent() {}

void FluidSimComponent::ResizeInnerCage(float width, float length, float height) {

	innerCage.scale.x = width;
	innerCage.scale.y = length;
	innerCage.scale.z = height;

	innerBoundingBox.generateFromBoundingBox(innerCage);
	innerBoundingBox.updateBuffers();

	// GENERATE PARTICLES
	vec3 minBounds = { -width, -length, -height };
	vec3 maxBounds = { width, length, height };

	// FILL VECTOR
	particles.clear();
	for (float x = minBounds.x; x <= maxBounds.x; x += 0.5f) {
		for (float y = minBounds.y; y <= maxBounds.y; y += 0.5f) {
			for (float z = minBounds.z; z <= maxBounds.z; z += 0.5f) {

				Particle temp{ vec3{x, y, z }, vec3{0.0f} };
				particles.push_back(temp);

			}
		}
	}

}

void FluidSimComponent::ResizeOuterCage(float width, float length, float height) {

	outerCage.scale.x = width;
	outerCage.scale.y = length;
	outerCage.scale.z = height;

	outerBoundingBox.generateFromBoundingBox(outerCage);
	outerBoundingBox.updateBuffers();

}

void FluidSimComponent::Draw(Camera& camera) {

	simulateTimeStep(0.001f);

	// CREATE SSBO POS VECTOR
	vector<vec4> particlePosSSBO;

	for (const Particle& p : particles) {
		particlePosSSBO.push_back(vec4{ p.position, 1.0f });
	}

	shaderPipelineComponent.updateParticleSSBO(particlePosSSBO);

	shaderPipelineComponent.Draw(camera, innerCage, outerCage, innerBoundingBox, outerBoundingBox, particles.size());

}

void FluidSimComponent::simulateTimeStep(float timeStep) {

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