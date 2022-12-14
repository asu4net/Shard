#version 330

uniform sampler2D u_texture;

struct VertexOutput
{
    vec4 color;
    float useTexture;
    vec2 texCoord;
};

in VertexOutput vertexOutput;

out vec4 FragColor;

void main()
{
    if (vertexOutput.useTexture != 0)
    {
        vec4 textureColor = texture(u_texture, vertexOutput.texCoord);
        vec4 finalColor = textureColor * vertexOutput.color;
        
        if (finalColor.a < 0.1)
            discard;
        
        FragColor = finalColor;
        return;
    }

    FragColor = vertexOutput.color;
}