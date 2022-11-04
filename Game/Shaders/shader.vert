#version 330
in vec3 aPosition;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

uniform vec4 u_color;
uniform float u_useTexture;

struct VertexOutput
{
    vec4 color;
    float useTexture;
    vec2 texCoord;
};

out VertexOutput vertexOutput;

void main()
{
    vertexOutput.color = u_color;
    vertexOutput.useTexture = u_useTexture;
    vertexOutput.texCoord = texCoord;

    gl_Position = u_projection * u_view * u_model * vec4(aPosition, 1.0);
}