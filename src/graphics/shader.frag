#version 330 core

in vec2 TexCoord;
in vec3 Normals;

out vec4 FragColor;

uniform sampler2D Texture;
uniform vec3 lightColor;
uniform float ambientIntensity;
void main()
{
	vec3 objectTexture = texture(Texture, TexCoord).xyz;
	FragColor = vec4(lightColor * objectTexture * ambientIntensity, 1.0);
}
	