#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 blockID;
const float textureSize = 1.0 / 16.0; // Using a 16x16 Atlas

out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = vec2(aTexCoord.x + (textureSize * blockID.x), aTexCoord.y + (textureSize * blockID.y));
	// TexCoord = aTexCoord;
}