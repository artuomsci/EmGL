#version 300 es

in vec3 VertexPosition;
in vec3 VertexNorm;
in vec3 VertBaryCoord;
in vec2 VertTexCoord;

uniform mat4 ModelViewMatr;
uniform mat4 ProjectionMatr;
uniform mat4 ModNormalMatr;

uniform float glPntSize;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;
out vec3 vBaryCoord;

void main(void)
{
    vec4 tempPos = ModelViewMatr * vec4(VertexPosition, 1.0);
    vPosition = tempPos.xyz;
    vTexCoord = VertTexCoord;
    vBaryCoord = VertBaryCoord;

    gl_Position = ProjectionMatr * tempPos;
    gl_PointSize = 4.0;
}
