#version 330 core

in vec2 TexCoord;
in vec3 Normals;

out vec4 FragColor;

uniform sampler2D Texture;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform float ambientIntensity;

void main()
{
	vec3 objectTexture = texture(Texture, TexCoord).xyz;
	vec3 objectColor = lightColor * objectTexture;

	// Ambient
	vec3 ambient = lightColor * ambientIntensity;

	// Diffuse
	float diffuseStrength = max(0.0, dot(lightPosition, Normals));
	vec3 diffuse = diffuseStrength * lightColor;

	// Specular
	vec3 specular;

	vec3 lighting = ambient + diffuse + specular;

	FragColor = vec4(lighting * objectTexture, 1.0);
}
	