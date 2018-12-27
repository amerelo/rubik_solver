#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinates;

uniform mat4	mvp_matrix;

out vec2	vS_tex_coord;

void		main()
{
	vS_tex_coord = texture_coordinates;

	gl_Position = mvp_matrix * vec4(position, 1.0);
}
