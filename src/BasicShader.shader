#vertex shader
#version 330 core
uniform mat4 translate;

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCood;

out vec2 TextCood;
void main()
{
	gl_Position = translate * position ;
	TextCood = texCood;
};
#fragment shader
#version 330 core

in vec2 TextCood;
layout(location = 0)out vec4 color;
uniform vec4 u_Color;
uniform sampler2D u_Texture;
void main()
{
	vec4 textColor = texture(u_Texture, TextCood);
	color = textColor;
};