#ifdef VERTEX
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelMatrix;
layout (std430, binding = 0) buffer CameraBuffer 
{
    mat4 projectionMatrix;
    mat4 viewMatrix;
    vec3 pos;
} camera;

void main()
{
    gl_Position = camera.projectionMatrix * camera.viewMatrix * modelMatrix * vec4(aPos, 1.0);
}
#endif


#ifdef FRAGMENT
layout (location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(1);
}
#endif