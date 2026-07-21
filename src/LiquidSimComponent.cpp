#pragma once

#include "LiquidSimComponent.h"

LiquidSimComponent::LiquidSimComponent() {

	Resize(1.0f, 1.0f, 1.0f);
	points.push_back(glm::vec3(0, 0, 0));

}

LiquidSimComponent::~LiquidSimComponent() {}

void LiquidSimComponent::Resize(unsigned int width, unsigned int length, unsigned int height) {

	this->width = width;
	this->length = length;
	this->height = height;

	cage.scale.x = length;
	cage.scale.y = width;
	cage.scale.z = height;

}

void LiquidSimComponent::Draw(Shader& shader) {

	cage.Draw(shader);

}