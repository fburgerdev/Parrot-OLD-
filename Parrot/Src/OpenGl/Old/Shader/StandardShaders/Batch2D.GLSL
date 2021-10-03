#shader vertex
#version 330
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;
layout(location = 2) in vec4 a_tint;

uniform vec2 u_windowDim;
uniform vec2 u_offset;

out vec2 v_texCoords;
flat out vec4 v_tint;

void main()
{
	gl_Position = vec4(2.0f * (u_offset.x + a_position.x) / u_windowDim.x - 1.0f, 1.0f - 2.0f * (u_offset.y + a_position.y) / u_windowDim.y, a_position.z / 255.0f, 1.0f);

	v_texCoords = a_texCoords;
	v_tint = a_tint;
}

#shader fragment
#version 330
out vec4 color;

in vec2 v_texCoords;
flat in vec4 v_tint;

uniform sampler2D u_texture;
uniform int u_flatShading;

void main()
{
	if (u_flatShading == 1)
		color = v_tint;
	else 
		color = texture(u_texture, v_texCoords).r * v_tint;
}
