#shader vertex
#version 330
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

flat out vec4 v_color;

// projection
uniform vec2 u_windowDim;
uniform int u_isOrthographic;
uniform vec3 u_camPos;
uniform vec2 u_camFactor;
vec4 GetScreenPos(vec3 position)
{	
	if (u_isOrthographic == 1)
		return vec4((position.xy - u_camPos.xy) * u_camFactor, 0.0f, 1.0f);
	else
		return vec4(2.0f * position.x / u_windowDim.x - 1.0f, 1.0f - 2.0f * position.y / u_windowDim.y, a_position.z / 255.0f, 1.0f);
}

void main()
{
	gl_Position = GetScreenPos(a_position); //vec4(2.0f * a_position.x / u_windowDim.x - 1.0f, 1.0f - 2.0f * a_position.y / u_windowDim.y, a_position.z / 255.0f, 1.0f);

	v_color = a_color;
}

#shader fragment
#version 330
out vec4 color;

flat in vec4 v_color;

void main()
{
	color = v_color;
}
