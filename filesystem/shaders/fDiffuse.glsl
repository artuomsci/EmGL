#version 300 es

precision highp float;

in vec3 vPosition;
in vec3 vBaryCoord;

out vec4 FragColor;

//--------------- material parameters
uniform vec3 Kd; // Diffuse reflectivity

void main(void)
{
     FragColor = vec4(Kd, 1.0);
     //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
