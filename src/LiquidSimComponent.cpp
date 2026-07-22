#pragma once

#include "LiquidSimComponent.h"

LiquidSimComponent::LiquidSimComponent() {

	Resize(1.0f, 1.0f, 1.0f);
	points.push_back(glm::vec3(0, 0, 0));

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
		LineVertex{ glm::vec4(maxX, minY, minZ, 0.0f),		glm::vec4(1.0f) },
		LineVertex{ glm::vec4(minX, minY, minZ, 0.0f),		glm::vec4(1.0f) },

		LineVertex{ glm::vec4(maxX, maxY, minZ, 0.0f),		glm::vec4(1.0f) },
		LineVertex{ glm::vec4(minX, maxY, minZ, 0.0f),		glm::vec4(1.0f) },

		LineVertex{ glm::vec4(maxX, minY, maxZ, 0.0f),		glm::vec4(1.0f) },
		LineVertex{ glm::vec4(minX, minY, maxZ, 0.0f),		glm::vec4(1.0f) },

		LineVertex{ glm::vec4(maxX, maxY, maxZ, 0.0f),		glm::vec4(1.0f) },
		LineVertex{ glm::vec4(minX, maxY, maxZ, 0.0f),		glm::vec4(1.0f) }
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

}