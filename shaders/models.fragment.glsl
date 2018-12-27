#version 410

uniform sampler2D	tex;
uniform vec3		camera_pos;
uniform vec3        light_pos;

               // All in world coordinates:
in vec3				vS_position;
in vec3				vS_normal;
in vec2             vS_tex_coord;

out vec4			out_fragment;

void main()
{
    vec4    surface_color = texture(tex, vS_tex_coord);
    vec3    surface_to_camera = normalize(camera_pos - vS_position);
    vec3    final_color = vec3(0.0);
    vec3    surface_to_light;
    vec3    ambient;
    vec3    diffuse;
    vec3    specular;
    float   attenuation_coef = 1.0;
    float   diffuse_coef;
    float   specular_coef;
    vec3    light_position = light_pos;
    vec3    light_color = vec3(1.0);
    float   light_power = 1.0;
    float   light_attenuation = 0.008;
    float   light_ambient = 0.38;
    float   surface_shine = 1000.0;

//    surface_color.a = 0.3;
    surface_to_light = normalize(light_position - vS_position);
    attenuation_coef = 1.0 / (1.0 + light_attenuation * pow(distance(light_position, vS_position), 2));
    ambient = light_ambient * surface_color.rgb * light_color;
    diffuse_coef = max(0.0, dot(vS_normal, surface_to_light));
    diffuse = diffuse_coef * surface_color.rgb * light_color;
    specular_coef = 0.0;
    if (diffuse_coef > 0.0)
        specular_coef = pow(max(0.0, dot(vS_normal, normalize(surface_to_camera + surface_to_light))), surface_shine);
    specular = specular_coef * surface_color.rgb * light_color;
    final_color += ambient + attenuation_coef * (diffuse + specular);

    out_fragment = vec4(final_color.rgb, surface_color.a);
//    out_fragment = vec4(1.0);
}