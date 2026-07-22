#version 430 core

out vec4 FragColor;

in vec3 color;
in vec3 intersectionPoint;

uniform vec3 u_camPos;

#define CAGE_ALPHA 0.2f
#define SPHERE_RADIUS 0.5f

bool intersectingSphere(vec3 orig);
float distBetweenPointAndLine(vec3 P, vec3 A, vec3 B);

void main(){
	
	FragColor = vec4(1.0f, 1.0f, 1.0f, CAGE_ALPHA);

	if (intersectingSphere(vec3(0.0f))) FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);

}

bool intersectingSphere(vec3 orig) {
	float d = distBetweenPointAndLine(orig, intersectionPoint, u_camPos);
	return d <= SPHERE_RADIUS;
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