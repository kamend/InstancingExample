#version 120
#extension GL_EXT_gpu_shader4 : require

attribute mat4 transformmatrix;

varying vec4 colorVarying;
varying vec4 position;
varying vec3 normal;

void main() {
	
	mat4 mvp = gl_ModelViewProjectionMatrix * transformmatrix;
	vec4 pos = gl_Vertex;
	
	normal = gl_NormalMatrix * gl_Normal;
	position = gl_ModelViewMatrix * gl_Vertex;
	
	gl_Position = mvp * pos;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}