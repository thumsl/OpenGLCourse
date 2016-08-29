#version 330

in vec3 fragPosition;
in vec2 fragTexture;
in vec3 fragNormal;

out vec4 fragColor;

uniform sampler2D sampler;

uniform mat4 transformationMatrix;
uniform mat4 normalTransformationMatrix;

uniform vec3 ambientLightColor;
uniform float ambientLightIntensity;

uniform vec3 pointLightColor;
uniform vec3 pointLightPosition;
uniform float pointLightIntensity;
uniform float pointLightAttenuation;

void main() {
	// AMBIENT LIGHT
	vec4 ambientColor = vec4(ambientLightColor * ambientLightIntensity, 1.0f);

	// POINT LIGHT
	vec4 diffuseColor = vec4(0, 0, 0, 0);

	vec3 normal = vec3(normalize(normalTransformationMatrix * vec4(fragNormal, 1.0f)));
	vec3 position = mat3(transformationMatrix) * fragPosition;

	vec3 lightToPixel = pointLightPosition - position;

	float diffuseFactor = dot(normal, lightToPixel);

	if (diffuseFactor > 0) {
		float distance = length(lightToPixel);
		float attenuation = 1.0f / (1.0f + pointLightAttenuation * distance + pointLightAttenuation * (distance * distance));

		diffuseColor = vec4(pointLightColor * diffuseFactor * attenuation * pointLightIntensity, 1.0f); // MULTIPLY BY INTENSITY

	}

    fragColor = vec4(texture2D(sampler, fragTexture).xyz, 1.0f) * (diffuseColor + ambientColor);
}
