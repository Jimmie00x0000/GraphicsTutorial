attribute vec4 position;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

// vertex shader ����ں���
void main() {
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * position;    
}