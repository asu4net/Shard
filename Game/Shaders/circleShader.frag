#version 330

struct VertexOutput
{
    vec3 localPosition;
    vec4 color;
    float thickness;
    float fade;
};

in VertexOutput output;

out vec4 FragColor;

void main()
{
    // Calculate distance and fill circle with white
    vec2 localPos = vec2(output.localPosition.x * 2, output.localPosition.y * 2);
    float distance = 1.0 - length(localPos);
    vec3 color = vec3(smoothstep(0.0, output.fade, distance));

    color *= vec3(smoothstep(output.thickness + output.fade, output.thickness, distance));

    // Set output color
    if (color.x == 0 && color.y == 0 && color.z == 0)
     discard;

    FragColor = vec4(color, 1.0);

    vec3 circleColor = vec3(output.color.r, output.color.g, output.color.b);
    FragColor.rgb *= circleColor;
}