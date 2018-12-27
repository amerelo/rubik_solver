#version 410

uniform sampler2D	frame_tex;
uniform sampler2D	alpha_tex;
uniform float       alpha_indice;

               // All in world coordinates:
in vec2             vS_tex_coord;

out vec4			out_fragment;

void main()
{
    vec4    frame_surface_color = texture(frame_tex, vS_tex_coord);
    vec4    alpha_surface_color = texture(alpha_tex, vS_tex_coord);

    out_fragment = vec4(frame_surface_color.rgb, alpha_surface_color.r + (alpha_indice - 1));
//    out_fragment = vec4(1.0);
}