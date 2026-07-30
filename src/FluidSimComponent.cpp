#pragma once

#include "FluidSimComponent.h"

using namespace glm;

FluidSimComponent::FluidSimComponent() {

	ball.scale = vec3(2.0f);
	ball.position.z -= 4.0f;

	innerBoundingBox.tint = innerBoundingBoxColor;
	outerBoundingBox.tint = outerBoundingBoxColor;

	ResizeInnerCage(vec3{ 1.0f, 1.0f, 1.0f });
	ResizeOuterCage(vec3{ 16.0f, 16.0f, 16.0f });

}

FluidSimComponent::~FluidSimComponent() {}

void FluidSimComponent::SetInnerCagePos(vec3 position) {

	physicsPlay = false;

	innerCage.position = position;

	innerBoundingBox.generateFromBoundingBox(innerCage);
	innerBoundingBox.updateBuffers();

	FillInnerCage();

}


void FluidSimComponent::SetInnerCageRot(vec3 rotation) {

	physicsPlay = false;

	innerCage.rotation = rotation;

	innerBoundingBox.generateFromBoundingBox(innerCage);
	innerBoundingBox.updateBuffers();

	FillInnerCage();

}

void FluidSimComponent::ResizeInnerCage(vec3 scale) {

	physicsPlay = false;

	innerCage.scale = scale;

	innerBoundingBox.generateFromBoundingBox(innerCage);
	innerBoundingBox.updateBuffers();

	FillInnerCage();

}

void FluidSimComponent::ResizeOuterCage(vec3 scale) {

	physicsPlay = false;

	outerCage.scale = scale;

	outerBoundingBox.generateFromBoundingBox(outerCage);
	outerBoundingBox.updateBuffers();

}

void FluidSimComponent::FillInnerCage() {

	vec3 minBounds = { -0.5f, -0.5f, -0.5f };
	vec3 maxBounds = { 0.5f, 0.5f, 0.5f };

	// FILL VECTOR
	particles.clear();
	particlePosSSBO.clear();
	for (float x = minBounds.x; x <= maxBounds.x; x += (particleDensity / innerCage.scale.x) ) {
		for (float y = minBounds.y; y <= maxBounds.y; y += (particleDensity / innerCage.scale.y) ) {
			for (float z = minBounds.z; z <= maxBounds.z; z += (particleDensity / innerCage.scale.z) ) {

				Particle temp{ vec3{x, y, z }, vec3{0.0f, 1.0f, 0.0f} };
				temp.position = vec3(innerCage.getModelMatrix() * vec4(temp.position, 1.0f));
				particles.push_back(temp);
				particlePosSSBO.push_back(vec4(temp.position, 1.0f));

			}
		}
	}

}

void FluidSimComponent::Draw(Camera& camera) {

	if (physicsPlay) SimulateTimeStep(0.0001f);

	shaderPipelineComponent.updateParticleSSBO(particlePosSSBO);
	shaderPipelineComponent.Draw_Particles(camera, innerCage, outerCage, particles.size());
	shaderPipelineComponent.Draw_BoundingBoxes(camera, innerBoundingBox, outerBoundingBox);
	shaderPipelineComponent.Draw_Mesh(camera, ball);

}

void FluidSimComponent::SimulateTimeStep(float timeStep) {

	const float RESTITUTION { 0.8f };

	for (int i = 0; i < particles.size(); ++i) {

		Particle& particle = particles[i];

		// GRAVITY
		particle.velocity += vec3(0.0f, 0.0f, -9.8);



		vec3 nextPosition = particle.position + particle.velocity * timeStep;

		// CAGE COLLISION CHECK
		vec3 minBounds = { -outerCage.scale.x / 2.0f, -outerCage.scale.y / 2.0f, -outerCage.scale.z / 2.0f };
		vec3 maxBounds = { outerCage.scale.x / 2.0f, outerCage.scale.y / 2.0f, outerCage.scale.z / 2.0f };

		for (int component = 0; component < 3; ++component) {

			if (!(minBounds[component] < nextPosition[component] && maxBounds[component] > nextPosition[component]))	// if new position is outside bounds, move particle to intersection and redirect velocity
			{

				float intersectedBoundsValue = (minBounds[component] >= nextPosition[component]) ? minBounds[component] : maxBounds[component];

				// Move particle out of bounds to a point where redirected velocity will correctly position it at end of timestep function
				float t = (intersectedBoundsValue - particle.position[component]) / (nextPosition[component] - particle.position[component]);

				// Ensure t is an expected value, if not then the difference is small enough that we don't need to move the position
				if (0.0f <= t && t <= 1.0f) {
					particle.position = (nextPosition - particle.position) * (t + 1.0f) + particle.position;
				}

				vec3 normal{ 0.0f };
				normal[component] = 1.0f;

				// Calculate new velocity
				particle.velocity = reflect(particle.velocity, normal);
				particle.velocity *= RESTITUTION;			// energy lost

			}

		}

		// SPHERE COLLISION CHECK
		if (distance(nextPosition, ball.position) < 2.0f) {

			vec3 normal = normalize(nextPosition - ball.position);

			particle.velocity = reflect(particle.velocity, normal);
			particle.velocity *= 0.8f; // energy lost

		}



		// UPDATE POSITION
		particle.position += particle.velocity * timeStep;
		particlePosSSBO[i] = vec4(particle.position, 1.0f);

	}

}