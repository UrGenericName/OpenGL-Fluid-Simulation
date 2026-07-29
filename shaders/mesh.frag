#version 430 core

out vec4 FragColor;

in vec3 color;
in vec3 normal;
in vec3 tint;
in vec3 intersectionPoint;

uniform vec3 u_camPos;
uniform vec3 u_tint;

#define MIN_BRIGHTNESS 0.5f
#define MAX_BRIGHTNESS 1.0f

void main() {
	
	vec3 ray = normalize(intersectionPoint - u_camPos);

	float brightness = abs(dot(ray, normal)) * (MAX_BRIGHTNESS - MIN_BRIGHTNESS) + MIN_BRIGHTNESS;

	FragColor = vec4( vec3(brightness) * u_tint, 1.0f );

}