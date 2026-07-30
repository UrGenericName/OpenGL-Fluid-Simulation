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
uniform float u_nearPlane;
uniform float u_farPlane;
uniform unsigned int u_particleCount;
uniform float u_particleRadius;
uniform vec3 u_cageSize;

// FUNCTION SIGNATURES
void drawParticle(vec3 orig);
float distBetweenPointAndLine(vec3 P, vec3 A, vec3 B, out vec3 closestPoint);

#define CAGE_ALPHA 0.2f
#define SPHERE_RADIUS 0.125f / 4.0f

void main(){
	
	gl_FragDepth = 1.0f;
	FragColor = vec4(1.0f, 1.0f, 1.0f, CAGE_ALPHA);

	for (int i = 0; i < u_particleCount; ++i) {
		drawParticle( particles[i].xyz );	
	}

}



void drawParticle(vec3 orig) {

	vec3 closestPoint;
	float d = distBetweenPointAndLine(orig, intersectionPoint, u_camPos, closestPoint);

	if (d <= u_particleRadius) {
		
		float z = distance(orig, u_camPos);
		gl_FragDepth = (u_farPlane * (z - u_nearPlane)) / (z * (u_farPlane - u_nearPlane));
		FragColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f);


	}

}

float distBetweenPointAndLine(vec3 P, vec3 A, vec3 B, out vec3 closestPoint) {
	
	// distance = ||v X QP|| / ||v||

	// P: point to test for
	// Q: point on line
	// v: line vector

	vec3 Q = B;
	vec3 QP = P - Q;

	vec3 v = A - B;

	float t = dot(QP, v) / dot(v, v); 
	closestPoint = v * t + Q; 

	float d = length( cross(v, QP) ) / length( v );

	return d;

}