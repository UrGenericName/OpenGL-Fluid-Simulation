#version 430 core

// LAYOUTS
layout(std430, binding = 0) readonly buffer ParticleBuffer {
    vec4 particles[];
};

// OUTPUT
out vec4 FragColor;

// INPUT
in vec3 color;
in vec3 intersectionPoint;

// UNIFORMS
uniform vec3 u_camPos;
uniform unsigned int u_particleCount;
uniform vec3 u_cageSize;

// FUNCTION SIGNATURES
void drawSphere(vec3 orig);
float distBetweenPointAndLine(vec3 P, vec3 A, vec3 B);

#define CAGE_ALPHA 0.2f
#define SPHERE_RADIUS 0.125f / 4.f



void main(){
	
	FragColor = vec4(1.0f, 1.0f, 1.0f, CAGE_ALPHA);

	for (int i = 0; i < u_particleCount; ++i) {
		drawSphere( particles[i].xyz );
	}

}



void drawSphere(vec3 orig) {

	float d = distBetweenPointAndLine(orig, intersectionPoint, u_camPos);

	if (d <= SPHERE_RADIUS) {

		float x_normalized = (orig.x + u_cageSize.x / 2.0f) / (u_cageSize.x * 2.0f);
		float y_normalized = (orig.y + u_cageSize.y / 2.0f) / (u_cageSize.y * 2.0f);
		float z_normalized = (orig.z + u_cageSize.z / 2.0f) / (u_cageSize.z * 2.0f);

		FragColor = vec4( x_normalized, y_normalized, z_normalized, 1.0f);

	}

}

float distBetweenPointAndLine(vec3 P, vec3 A, vec3 B) {
	
	// distance = ||v X QP|| / ||v||

	// P: point to test for
	// Q: point on line
	// v: line vector

	vec3 Q = B;
	vec3 QP = P - Q;

	vec3 v = A - B;

	float d = length( cross(v, QP) ) / length( v );

	return d;

}