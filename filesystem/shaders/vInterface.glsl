#version 300 es

in vec2 VertexPosition;
in vec2 VertTexCoord;
in vec4 VertColor;

uniform mat4 ProjectionMatr;

out vec2 vTexCoord;
out vec4 vColor;

void main(void)
{
    vTexCoord   = VertTexCoord;
    vColor      = VertColor;

    gl_Position = ProjectionMatr * vec4(VertexPosition.xy, 0.0, 1.0);
}

