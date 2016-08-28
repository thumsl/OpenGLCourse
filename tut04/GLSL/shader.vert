#version 330

layout (location = 0) in vec3 position;

uniform mat4 MVP;

out vec3 color;

void main() {
	color = vec3(1.0f, 0.0f, 1.0f);
	gl_Position = MVP * vec4(position, 1.0);
}
