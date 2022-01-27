#version 300 es

in vec3 VertexPosition;
in vec3 VertBaryCoord;

uniform mat4 ModelViewMatr;
uniform mat4 ProjectionMatr;

out vec3 vBaryCoord;

void main(void)
{
    vec4 tempPos = ModelViewMatr * vec4(VertexPosition, 1.0);

    vBaryCoord = VertBaryCoord;

    gl_Position = ProjectionMatr * tempPos;
}
