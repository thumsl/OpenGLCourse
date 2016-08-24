#version 330

layout (location = 0) in vec3 position;

uniform float offset;

out vec3 color;

void main() {
	color = vec3(1.0f, 0.0f, 1.0f);
	gl_Position = vec4(position.x + offset, position.y, position.z, 1.0);
}
