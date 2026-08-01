#pragma once

#include <glm/glm.hpp>

using namespace glm;

struct Particle {

	vec3 position;
	vec3 velocity;
	float density;
	const float mass = 1.0f;

};