#version 300 es

precision highp float;

in vec3 vPosition;
in vec3 vNormal;
in vec3 vBaryCoord;

out vec4 FragColor;

//--------------- material parameters
uniform vec3 Kd; // Diffuse reflectivity
uniform vec3 Ka; // Ambient reflectivity
uniform vec3 Ks; // Specular reflectivity
uniform float Shininess; // Specular shininess factor

void main(void)
{
    vec3  LightIntensity;
    vec3  LightPosition;

    LightIntensity = vec3(0.6, 0.6, 0.6);
    LightPosition = vec3(0.0, 0.0, -35.0);

    vec3 n = normalize(cross(dFdx(vPosition), dFdy(vPosition)));
    vec3 s = normalize(LightPosition - vPosition);
    vec3 v = normalize(-vPosition);
    vec3 r = reflect(-s, n);
    float sDotN = max(dot(s, n), 0.0);

    vec3 clr1 = Ka + Kd * sDotN;
    vec3 clr2 = Ks * pow(max(dot(r, v), 0.0), Shininess) * sDotN / sDotN;

    vec4 outclr = vec4((clr1 + clr2) * LightIntensity, 1.0);

    //FragColor = outclr;
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}



