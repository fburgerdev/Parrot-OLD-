#shader vertex
#version 330
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;
layout(location = 2) in vec4 a_color;

out vec2 v_texCoords;
flat out vec4 v_color;

struct OrthographicCamera
{
	vec3 pos;
	vec2 dimFactor;
};
struct PerspectiveCamera
{
	vec3 pos;
	mat4 projMat;
	mat3 viewMat;
};
struct Camera
{
	OrthographicCamera orthographicCamera;
	PerspectiveCamera perspectiveCamera;
	int cameraType; // 0 <=> OrthographicCamera; 1 <=> PerspectiveCamera;

	vec4 GetScreenPos(vec3 position)
	{
		if (cameraType == 0)
			return vec4((position.xy - orthographicCamera.pos.xy) * orthographicCamera.dimFactor, 0.0f, 1.0f);
		else
			return perspectiveCamera.projMat * vec4(perspectiveCamera.viewMat * (position - perspectiveCamera.pos), 1.0f);
	}
};
uniform Camera u_Camera;

void main()
{
	gl_Position = u_Camera.GetScreenPos(a_position);

	v_texCoords = a_texCoords;
	v_color = a_color;
}

#shader fragment
#version 330
out vec4 color;

in vec2 v_texCoords;
flat in vec4 v_color;

uniform sampler2D u_texture;
void main()
{
	color = texture(u_texture, v_texCoords) * v_color;
}
