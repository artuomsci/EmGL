#version 300 es

precision highp float;

in vec3 vBaryCoord;

out vec4 FragColor;

//--------------- material parameters
uniform vec3 Kd; // Diffuse reflectivity

void main(void)
{
    if(any(lessThan(vBaryCoord, vec3(0.02))))
    {
        //FragColor = vec4(Kd.x, Kd.y, Kd.z, 1.0);
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }

    else
        discard;
}



