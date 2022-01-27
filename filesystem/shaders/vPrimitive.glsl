#version 300 es

in vec3 VertexPosition;

uniform mat4 ModelViewMatr;
uniform mat4 ProjectionMatr;

uniform float glPntSize;

void main(void)
{
    vec4 tempPos = ModelViewMatr * vec4(VertexPosition, 1.0);
    gl_Position = ProjectionMatr * tempPos;
    gl_PointSize = 4.0;
}
