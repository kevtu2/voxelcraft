#version 330 core

in vec3 Coords;
in vec2 TexCoord;
in vec3 Normals;

out vec4 FragColor;

uniform sampler2D Texture;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform float ambientIntensity;
uniform float specularIntensity;

void main()
{
	vec3 objectTexture = texture(Texture, TexCoord).xyz;
	vec3 objectColor = lightColor * objectTexture;
	
	vec3 lightVector = lightPosition - Coords;

	// Ambient
	vec3 ambient = lightColor * ambientIntensity;

	// Diffuse
	float diffuseStrength = max(0.0, dot(lightVector, Normals));
	vec3 diffuse = diffuseStrength * lightColor;

	// Specular
	vec3 cameraSource = normalize(cameraPosition);
	vec3 reflection = normalize(reflect(-lightVector, Normals));
	float specularStrength = max(0.0, dot(cameraSource, reflection));
	specularStrength = pow(specularStrength, specularIntensity);
	vec3 specular = specularStrength * lightColor;

	vec3 lighting = ambient + diffuse + specular;

	FragColor = vec4(lighting * objectTexture, 1.0);
}
	