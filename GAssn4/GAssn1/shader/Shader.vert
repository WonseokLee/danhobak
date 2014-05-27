varying vec3 N, L, E, H;
varying vec2 texcoord;
void main()
{
gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
vec4 eyePosition = gl_ModelViewMatrix * gl_Vertex;
vec4 eyeLightPos = gl_LightSource[0].position;
N = normalize(gl_NormalMatrix * gl_Normal);
L = normalize(eyeLightPos.xyz - eyePosition.xyz);
E = -normalize(eyePosition.xyz);
H = normalize(L + E);
texcoord = vec2(gl_MultiTexCoord0);
}