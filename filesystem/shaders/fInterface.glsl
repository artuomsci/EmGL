#version 300 es

precision highp float;

in vec2 vTexCoord;
in vec4 vColor;

out vec4 FragColor;

uniform sampler2D texture0;

void main(void)
{
     FragColor = vColor * texture2D(texture0, vTexCoord);
     //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
