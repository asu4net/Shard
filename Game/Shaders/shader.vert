#version 330
in vec3 aPosition;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

uniform vec4 u_color;

struct VertexOutput
{
    vec4 color;
};

out VertexOutput output;

void main()
{
    output.color = u_color;
    gl_Position = u_projection * u_view * u_model * vec4(aPosition, 1.0);
}