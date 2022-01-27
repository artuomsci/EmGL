#version 300 es

precision highp float;

in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D texture0;

void main(void)
{
     FragColor = texture2D(texture0, vTexCoord);
     //gl_FragColor = vec4(vTexCoord.x, vTexCoord.y, 0.0, 1.0);
     //FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}
