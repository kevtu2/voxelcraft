#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D Texture;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	vec3 objectTexture = texture(Texture, TexCoord).xyz;
	FragColor = vec4(lightColor * objectColor * objectTexture, 1.0);
}
	