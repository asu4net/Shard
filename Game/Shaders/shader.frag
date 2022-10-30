#version 330

struct VertexOutput
{
    vec4 color;
};

in VertexOutput output;

out vec4 FragColor;

void main()
{
    FragColor = output.color;
}