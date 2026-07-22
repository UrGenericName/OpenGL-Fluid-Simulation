#pragma once

#include "LiquidSimComponent.h"

using namespace glm;

LiquidSimComponent::LiquidSimComponent() {

	Resize(1.0f, 1.0f, 1.0f);

}

LiquidSimComponent::~LiquidSimComponent() {}

void LiquidSimComponent::Resize(float width, float length, float height) {

	this->width = width;
	this->length = length;
	this->height = height;

	cage.scale.x = width;
	cage.scale.y = length;
	cage.scale.z = height;



	float maxX = width / 2.0f;
	float minX = -(width / 2.0f);

	float maxY = length / 2.0f;
	float minY = -(length / 2.0f);

	float maxZ = height / 2.0f;
	float minZ = -(height / 2.0f);

	lines.vertices = {
		LineVertex{ vec4(maxX, minY, minZ, 0.0f),		vec4(1.0f) },
		LineVertex{ vec4(minX, minY, minZ, 0.0f),		vec4(1.0f) },

		LineVertex{ vec4(maxX, maxY, minZ, 0.0f),		vec4(1.0f) },
		LineVertex{ vec4(minX, maxY, minZ, 0.0f),		vec4(1.0f) },

		LineVertex{ vec4(maxX, minY, maxZ, 0.0f),		vec4(1.0f) },
		LineVertex{ vec4(minX, minY, maxZ, 0.0f),		vec4(1.0f) },

		LineVertex{ vec4(maxX, maxY, maxZ, 0.0f),		vec4(1.0f) },
		LineVertex{ vec4(minX, maxY, maxZ, 0.0f),		vec4(1.0f) }
	};

	lines.indices = { 
		0, 1, 
		2, 3, 
		4, 5, 
		6, 7, 
		0, 2, 
		0, 4,
		1, 3,
		1, 5,
		2, 6,
		3, 7,
		4, 6,
		5, 7
	};

	lines.updateBuffers();

	// FILL VECTOR
	particles.clear();
	for (float x = minX; x <= maxX; x += 0.5f) {
		for (float y = minY; y <= maxY; y += 0.5f) {
			for (float z = minZ; z <= maxZ; z += 0.5f) {

				particles.push_back(vec4(x, y, z, 1.0f));

			}
		}
	}

	shaderPipelineComponent.updateParticleSSBO(particles);

}

void LiquidSimComponent::Draw(Camera& camera) {

	shaderPipelineComponent.Draw(camera, cage, lines, particles.size(), vec3(width, length, height));

}