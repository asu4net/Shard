#version 330

struct VertexOutput
{
    vec3 localPosition;
    vec4 color;
    float thickness;
    float fade;
};

in VertexOutput vertexOutput;

out vec4 FragColor;

void main()
{
    // Calculate distance and fill circle with white
    vec2 localPos = vec2(vertexOutput.localPosition.x * 2, vertexOutput.localPosition.y * 2);
    float distance = 1.0 - length(localPos);
    vec3 color = vec3(smoothstep(0.0, vertexOutput.fade, distance));

    color *= vec3(smoothstep(vertexOutput.thickness + vertexOutput.fade, vertexOutput.thickness, distance));

    // Set output color
    if (color.x == 0 && color.y == 0 && color.z == 0)
     discard;

    FragColor = vec4(color, 1.0);

    vec3 circleColor = vec3(vertexOutput.color.r, vertexOutput.color.g, vertexOutput.color.b);
    FragColor.rgb *= circleColor;
}