//#version 400 // GLSL version with core profile
uniform mat4 projMat, viewMat, modelMat;
in vec3 vPosition;
in vec3 vColor;
out vec4 color;

void main ()
{
    // Transform coordinates from local space to clipped space
    gl_Position = projMat * viewMat * modelMat * vec4 (vPosition, 1);
    color = vec4(vColor, 1.0); // RGBA color defined in [0,1]
}