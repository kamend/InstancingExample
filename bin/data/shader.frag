uniform sampler2D tex;
varying vec4 colorVarying;

varying vec4 position;
varying vec3 normal;

void main()
{
	vec3 lightPos = vec3(0,-400.0,0.0);
	vec3 color = vec3(0.8,0.8,0.3);
	vec3 eyeCoords = position.xyz;
	vec3 tnormal = normalize(normal);
	
	vec3 s = normalize(vec3(lightPos - eyeCoords));
	vec3 v = normalize(-eyeCoords);
	vec3 r = reflect(-s, tnormal);
	float sDotN = max(dot(s,tnormal),0.0);
	
	vec3 ambient = vec3(0.1,0.1,0.0);
	vec3 diffuse = color * sDotN;
	vec3 spec = vec3(0.0);
	
	float shine = 16.0;
	
	if(sDotN > 0.0) {
		spec = color * pow(max(dot(r,v),0.0), shine);
	}
	

	gl_FragColor = vec4(diffuse+spec+ambient,1.0);
}