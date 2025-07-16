#version 330 core

layout(location = 0) in vec2 aPos;

uniform mat4 projection;
uniform vec2 translation;

void main()
{
	vec4 pos = vec4(aPos + translation, 0.0, 1.0);
	gl_Position = projection * pos;
}