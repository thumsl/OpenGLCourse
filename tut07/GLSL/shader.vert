#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 normal;

uniform mat4 MVP;

out vec3 fragPosition;
out vec2 fragTexture;
out vec3 fragNormal;


void main() {
	fragPosition = position;
	fragTexture = texture;
	fragNormal = normal;

	gl_Position = MVP * vec4(position, 1.0);
}
