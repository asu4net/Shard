#version 330
in vec3 aPosition;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

uniform vec4 u_color;
uniform float u_spriteColor;
uniform float u_thickness;
uniform float u_fade;

struct VertexOutput
{
    vec3 localPosition;
    vec4 color;
    float thickness;
    float fade;
};

out VertexOutput output;

void main()
{
    //output pass...
    output.localPosition = aPosition;
    output.color = u_color;
    output.thickness = u_thickness;
    output.fade = u_fade;

    gl_Position = u_projection * u_view * u_model * vec4(aPosition, 1.0);
}