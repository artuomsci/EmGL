#version 300 es

in vec2 VertexPosition;
in vec2 VertTexCoord;

uniform mat4 ProjectionMatr;

out vec2 vTexCoord;

void main(void)
{
    vTexCoord = VertTexCoord;

    gl_Position = ProjectionMatr * vec4(VertexPosition.xy, 0.0, 1.0);
}

