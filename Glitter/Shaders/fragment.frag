#version 410 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    color = mix(texture(ourTexture1, TexCoord).rgba, texture(ourTexture2, TexCoord).rgba, vec4(texture(ourTexture2, TexCoord)).a * 0.2);
}
