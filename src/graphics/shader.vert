#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 atlasCoord;

const float textureSize = 0.0625f;

out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = vec2(aTexCoord.x + (atlasCoord.x * textureSize), aTexCoord.y + (atlasCoord.x * textureSize));
}